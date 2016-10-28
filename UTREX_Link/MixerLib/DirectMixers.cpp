// For using the input directly as an output

struct Mixer_DirectDelta : Mixer
{
    u16 Value;

    Mixer_DirectDelta() : Mixer(1, 0, 0, 0) { Reset(); }

    u16 Mix()
    {
        Value += *(Deltas[0]);
        return Value;
    }

    void Reset()
    {
        Value = 0;
    }
};

struct Mixer_DirectRange : Mixer
{
    Mixer_DirectRange() : Mixer(0, 1, 0, 0) {};

    u16 Mix()
    {
        return *(Ranges[0]);
    }
};

struct Mixer_DPadStateY : Mixer
{
    Mixer_DPadStateY() : Mixer(0, 0, 1, 0) {};

    u16 Mix()
    {
        // Assuming SDL DPad mapping
        State st = *(States[0]);

        if (st & SDL_HAT_UP)        return Mixer_Max;
        else if (st & SDL_HAT_DOWN) return Mixer_Min;
        else                        return Mixer_Center;
    }
};

struct Mixer_DPadStateX : Mixer
{
    Mixer_DPadStateX() : Mixer(0, 0, 1, 0) {};

    u16 Mix()
    {
        // Assuming SDL DPad mapping
        State st = *(States[0]);

        if (st & SDL_HAT_RIGHT)     return Mixer_Max;
        else if (st & SDL_HAT_LEFT) return Mixer_Min;
        else                        return Mixer_Center;
    }
};

struct Mixer_DirectButton : Mixer
{
    Mixer_DirectButton() : Mixer(0, 0, 0, 1) {};

    u16 Mix()
    {
        if (Buttons[0].Get()) return Mixer_Max;
        else return Mixer_Min;
    }
};
