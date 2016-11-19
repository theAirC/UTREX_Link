
struct Output
{
	Curve myCurve;
	Mixer *myMixer;

	Output() {}
	Output(Mixer *myMixer) : myMixer(myMixer) {}
	Output(Curve myCurve) : myCurve(myCurve) {}
	Output(Curve myCurve, Mixer *myMixer) : myCurve(myCurve), myMixer(myMixer) {}

    u16 Get()
    {
        return myCurve.Points[myMixer->Mix()];
    }
};
