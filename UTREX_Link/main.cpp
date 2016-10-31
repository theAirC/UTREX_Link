
#include "loop.cpp"

int main(int argc, char* argv[])
{
    ifdieSDL(SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC));

    //SDL_JoystickEventState(SDL_IGNORE);

    printf("\n""[=] %i joysticks were found.", SDL_NumJoysticks());
	ifdie(SDL_NumJoysticks() <= 0);
    printf("\n""[=] The names of the joysticks are:");

    for(int i = 0; i < SDL_NumJoysticks(); i++) {
        printf("\n""\t""%s\n", SDL_JoystickNameForIndex(i));

        SDL_Joystick* joystick = SDL_JoystickOpen(i);
        printf("\n""\t""%s\n", SDL_JoystickName(joystick));
        if (SDL_JoystickIsHaptic(joystick)) printf("\n""\t\t""with haptic");

        InputDevices.push_back(new InputJoystick(joystick));
    }

    for(size_t i = 0; i < InputDevices.size(); i++) {
        printf("\n""Deltas:  %d", InputDevices[i]->Deltas.Length);
        printf("\n""Ranges:  %d", InputDevices[i]->Ranges.Length);
        printf("\n""States:  %d", InputDevices[i]->States.Length);
        printf("\n""Buttons: %d", InputDevices[i]->Buttons.Count);
    }

    // Set up a input-mixer-output stream for testing

    Mixers.push_back(MixerList[1]()); // make a new mixer of the first type in the list

    for (size_t i = 0; i < Mixers[0]->Deltas.Length; i++) {
        Mixers[0]->Deltas[i] = &(InputDevices[0]->Deltas[i]);
    }

    for (size_t i = 0; i < Mixers[0]->Ranges.Length; i++) {
        Mixers[0]->Ranges[i] = &(InputDevices[0]->Ranges[i]);
    }

    for (size_t i = 0; i < Mixers[0]->States.Length; i++) {
        Mixers[0]->States[i] = &(InputDevices[0]->States[i]);
    }

    for (size_t i = 0; i < Mixers[0]->Buttons.Length; i++) {
        Mixers[0]->Buttons[i] = InputDevices[0]->Buttons.GetPointer(i);
    }

    Outputs.push_back(new Output(CurveLib.Identity));
    Outputs[0]->myMixer = Mixers[0];

	try {
		Serial mySerial("COM5");

		mySerial.myOutputs.push_back(Outputs[0]);

		while (1) {
			SDL_Delay(20);

			SDL_JoystickUpdate();
			for (size_t i = 0; i < InputDevices.size(); i++) InputDevices[i]->Update();
			
			mySerial.SendOutputs();
		}
	} catch (std::exception &e) {
		LogDie(e.what());
	}


    /*
    //ifdieSDL(SDL_CaptureMouse(SDL_TRUE));
    ifdieSDL(SDL_SetRelativeMouseMode(SDL_TRUE));

    ifdie(SDL_GetRelativeMouseMode() != SDL_TRUE);

    SDL_Window *MainWindow = SDL_CreateWindow("UTREX Link",
                                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              800, 600,
                                              SDL_WINDOW_MOUSE_CAPTURE);
    ifdie(MainWindow == NULL);

    int x = 123;
    int y = 123;

    SDL_Delay(500);
    printf("\n""%d", SDL_GetRelativeMouseState(&x, &y));

    while (1) {
        ifdieSDL(SDL_GetRelativeMouseState(&x, &y));
        printf("\n""%d, %d", x, y);
        SDL_Delay(500);
    }

    SDL_Delay(1000);
    SDL_DestroyWindow(MainWindow);
    */

    //while (1) loop();

    return 0;
}
