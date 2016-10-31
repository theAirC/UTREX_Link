
struct Output
{
    Mixer* myMixer;
	Curve myCurve;

	Output(Curve myCurve) : myCurve(myCurve) {}

    u16 Get()
    {
        return myCurve.Points[myMixer->Mix()];
    }
};
