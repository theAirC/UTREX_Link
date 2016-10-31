
struct Curve
{
    u16 Points[64 * 1024];
};

// Some prototype curves used as starting curves
const struct CurveLib_t
{
    Curve Zero;       // Outputs only 0
    Curve Identity;   // Output = input
	Curve Identity_R; // Output = input in revese (i.e. 0 is full and full is 0)
    Curve Step;       // Ouputs 0 for half lower values and full for the other half
	Curve Step_R;     // Same as Step, in reverse

    CurveLib_t()
    {
        // Warning: if you used "u16 i" instead of "u32 i" the loops would never end

        for (u32 i = 0; i < 64 * 1024; i++) Zero.Points[i] = 0;

		for (u32 i = 0; i < 32 * 1024; i++)         { Step.Points[i] = 0; Step_R.Points[i] = ~0; }
		for (u32 i = 32 * 1024; i < 64 * 1024; i++) { Step.Points[i] = ~0; Step_R.Points[i] = 0; }

		for (u32 i = 0; i < 64 * 1024; i++) { Identity.Points[i] = i; Identity_R.Points[i] = ~i; }
    }
} CurveLib;
