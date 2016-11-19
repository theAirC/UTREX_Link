// Holds all the relevant information for a particular input device (joystick, mouse, etc).
// Also provides a device specific method for updating these values.

class InputDevice
{
public:
    Array<Delta_t>  Deltas;
    Array<Range_t>  Ranges;
    Array<State_t>  States;
	Array<Button_t> Buttons;
    //Buttons_t Buttons;

    InputDevice(size_t DeltaCount, size_t RangeCount, size_t StateCount, size_t ButtonCount)
        : Deltas(DeltaCount),
          Ranges(RangeCount),
          States(StateCount),
          Buttons(ButtonCount)
    {
        Deltas.Fill(Delta_Center);
        Ranges.Fill(Range_Center);
        States.Fill(State_Center);
		Buttons.Fill(Button_Center);
        //Buttons.ClearAll();
    }
    virtual ~InputDevice() {};

    virtual void Update() {};
};

class InputJoystick : public InputDevice
{
private:
    SDL_Joystick* const myJoystick;

public:
    InputJoystick(SDL_Joystick* myJoystick)
        : InputDevice(SDL_JoystickNumBalls(myJoystick) * 2,
                      SDL_JoystickNumAxes(myJoystick),
                      SDL_JoystickNumHats(myJoystick),
                      SDL_JoystickNumButtons(myJoystick)),
          myJoystick(myJoystick)
    {}

    void Update()
    {
        for (size_t i = 0; i < Deltas.Length; i += 2) {
            // SDL gives 2 trackBall deltas at once, one for delta-x and one for delta-y
            SDL_JoystickGetBall(myJoystick, i, &Deltas[i], &Deltas[i + 1]);
        }

        for (size_t i = 0; i < Ranges.Length; i++) {
            Ranges[i] = ~(SDL_JoystickGetAxis(myJoystick, i) + 0x8000);
        }

        for (size_t i = 0; i < States.Length; i++) {
            States[i] = SDL_JoystickGetHat(myJoystick, i);
        }

        for (size_t i = 0; i < Buttons.Length; i++) {
			Buttons[i] = SDL_JoystickGetButton(myJoystick, i);
            //Buttons.Apply(i, SDL_JoystickGetButton(myJoystick, i));
        }
    }
};
