// Mixers mix (combine) and process one or more InputDevice fields.
// The abstract class Mixer holds pointers to the relevant input data to mix/process,
// as well as the Mixing function.

struct Mixer
{
    Array<Delta*> Deltas;
    Array<Range*> Ranges;
    Array<State*> States;
    Array<BitPointer> Buttons;

    Mixer(size_t DeltaCount, size_t RangeCount, size_t StateCount, size_t ButtonCount)
        : Deltas(DeltaCount),
          Ranges(RangeCount),
          States(StateCount),
          Buttons(ButtonCount)
    {}

    virtual u16 Mix() = 0;

    // The following methods are optional
    virtual void Reset() {};
};

template <class MixerType>
Mixer* MakeMixer()
{
    return new MixerType;
}

typedef Mixer* (*MixerMaker)();
