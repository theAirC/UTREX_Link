// Mixers mix (combine) and process one or more InputDevice fields.
// The abstract class Mixer holds pointers to the relevant input data to mix/process,
// as well as the Mixing function.

struct Mixer
{
    Array<const Delta_t *> Deltas;
    Array<const Range_t *> Ranges;
    Array<const State_t *> States;
    Array<const Button_t*> Buttons;

    Mixer(size_t DeltaCount, size_t RangeCount, size_t StateCount, size_t ButtonCount)
        : Deltas(DeltaCount),
          Ranges(RangeCount),
          States(StateCount),
          Buttons(ButtonCount)
    {
		Deltas.Fill(&Delta_Center);
		Ranges.Fill(&Range_Center);
		States.Fill(&State_Center);
		Buttons.Fill(&Button_Center);
		//Buttons.Fill(Buttons_Center.GetPointer(0));
	}

    virtual u16 Mix() = 0;

    // The following methods are optional
    virtual void Reset() {};
};
