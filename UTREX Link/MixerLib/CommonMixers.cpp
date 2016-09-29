// Common Mixer Functions

struct Mixer_ThrottleAndBrake : Mixer
{
    Mixer_ThrottleAndBrake() : Mixer(0, 2, 0, 0) {};

    // Range[0] is throttle
    // Range[1] is brake
    // Output < Mixer_Center is brake/reverse
    // Output > Mixer_Center is acceleration
    u16 Mix()
    {
        u16 Throttle = *(Ranges[0]) / 2; // Divide by 2, because we combine 2 ranges into 1 output
        u16 Brake = *(Ranges[1]) / 2;

        if (Brake > 0) return Mixer_Center - Brake;
        else return Mixer_Center + Throttle;
    }
};

struct Mixer_Average : Mixer
{
    Mixer_Average() : Mixer(0, 2, 0, 0) {};

    // Returns the average of 2 Ranges
    u16 Mix()
    {
        u16 R0 = *(Ranges[0]) / 2; // divide by 2 so that we don't overflow
        u16 R1 = *(Ranges[1]) / 2;
        return (R0 + R1);
    }
};

struct Mixer_Difference : Mixer
{
    Mixer_Difference() : Mixer(0, 2, 0, 0) {};

    // Returns the difference of 2 Ranges
    u16 Mix()
    {
        u16 R0 = *(Ranges[0]) / 2; // divide by 2 so that we don't overflow
        u16 R1 = *(Ranges[1]) / 2;
        return Mixer_Center + (R0 - R1);
    }
};

struct Mixer_RangeIfButton : Mixer
{
    Mixer_RangeIfButton() : Mixer(0, 1, 0, 1) {};

    // Outputs a range only if a button is pressed/active
    u16 Mix()
    {
        if (Buttons[0].Get()) return *(Ranges[0]);
        else return Mixer_Min;
    }
};
