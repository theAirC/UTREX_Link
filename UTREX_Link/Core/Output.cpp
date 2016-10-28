
struct Output
{
    Curve* myCurve;
    Mixer* myMixer;

    u16 Get()
    {
        return myCurve->Points[myMixer->Mix()];
    }
};
