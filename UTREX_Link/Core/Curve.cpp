
struct Curve
{
	u16 Scale;
	bool Inverted;
	bool isMirrorX;
	bool isMirrorCenter;

	u16 Points[64 * 1024];

	Curve() {}
	Curve(const char *filename) { load(filename); }

	void load(const char *filename)
	{
		// Note: reverts all modifications (invertions, dualX, dualY ...)
		Scale = 0;
		Inverted = false;
		isMirrorX = false;
		isMirrorCenter = false;

		size_t readSize = 0;
		SDL_RWops *SDL_FileHandle = SDL_RWFromFile(filename, "r");
		if (SDL_FileHandle) {
			readSize = SDL_RWread(SDL_FileHandle, Points, 1, sizeof(Points));
			SDL_RWclose(SDL_FileHandle);
		}

		if (readSize != sizeof(Points)) {
			for (u32 i = 0; i < asize(Points); i++) Points[i] = i; // Fill in some safe fallback values
			printf("\n""[!] Curve {");
			printf(filename);
			printf("} loading failed. Using identity curve fallback.");
		}
	}

	void applyScale(u16 newScale)
	{
		Scale = newScale;

		if (Scale != 0) for (u32 i = 0; i < asize(Points); i++) Points[i] = rounddiv(Points[i] * Scale, 64 * 1024);
	}

	void MirrorX()
	{
		// Mirrors and Copies the curve around the center of the X axis
		isMirrorX = true;

		u16 temp[asize(Points)];
		memcpy(temp, Points, sizeof(Points));

		for (u32 i = 0; i < asize(Points) / 2; i++) {
			u16 original_i = asize(Points) - 2 * (i + 1);
			Points[i] = temp[original_i];
		}
		for (u32 i = asize(Points) / 2; i < asize(Points); i++) {
			u16 original_i = 2 * i - asize(Points);
			Points[i] = temp[original_i];
		}
	}

	void MirrorCenter()
	{
		// Mirrors and Copies the curve around the center orgin (X-center, Y-center)
		isMirrorCenter = true;

		u16 temp[asize(Points)];
		memcpy(temp, Points, sizeof(Points));

		for (u32 i = 0; i < asize(Points) / 2; i++) {
			u16 original_i = asize(Points) - 2 * (i + 1);
			Points[i] = 0x7FFF - (temp[original_i] / 2);
		}
		for (u32 i = asize(Points) / 2; i < asize(Points); i++) {
			u16 original_i = 2 * i - asize(Points);
			Points[i] = 0x7FFF + (temp[original_i] / 2);
		}
	}

	void Invert()
	{
		// Inverts the Y axis (Max -> 0, 0 -> Max)
		Inverted = true;

		for (u32 i = 0; i < asize(Points); i++) Points[i] = ~Points[i];
	}

	void processParams(u32 params)
	{
		// Check for Mirrors
		if (params & (1 << 2)) {
			MirrorCenter();
		}
		if (params & (1 << 1)) {
			MirrorX();
		}
		// Check for Invertion
		if (params & (1 << 0)) {
			Invert();
		}
	}
};

/*
// Some prototype curves used as starting curves
const struct CurveLib_t
{
	Curve Zero;       // Outputs only 0
	Curve Identity;   // Output = input
	Curve Quarter;    // Output = input / 4
	Curve Step;       // Ouputs 0 for half lower values and full for the other half

	CurveLib_t()
	{
		// Warning: if you used "u16 i" instead of "u32 i" the loops would never end

		for (u32 i = 0; i < 64 * 1024; i++) Zero.Points[i] = 0;

		for (u32 i = 0; i < 32 * 1024; i++)         Step.Points[i] = 0;
		for (u32 i = 32 * 1024; i < 64 * 1024; i++) Step.Points[i] = ~0;

		for (u32 i = 0; i < 64 * 1024; i++) Identity.Points[i] = i;

		for (u32 i = 0; i < 64 * 1024; i++) Quarter.Points[i] = i / 4;
	}
} CurveLib;
*/
