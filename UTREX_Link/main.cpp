
#include "loop.cpp"

int main(int argc, char *argv[])
{
    ifdieSDL(SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC));

	try {
		// myConfig will hold the current configuration
		// if the config file does not exist, it will be automatically created
		Config myConfig("config.json");

		// read the config file and parse it
		// a faulty or incomplete file will be automatically fixed
		// This also populates the memory with the appropriate Mixers and Outputs,
		// as well as 'dummy' InputDevices.
		ifdie(myConfig.load() < 0);

		//SDL_JoystickEventState(SDL_IGNORE);

		printf("\n""[=] %i joysticks were found.", SDL_NumJoysticks());
		printf("\n""[=] The names of the joysticks are:");

		for(int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick *joystick = SDL_JoystickOpen(i);
			if (joystick) {
				printf("\n""\t""%s", SDL_JoystickName(joystick));
				if (SDL_JoystickIsHaptic(joystick)) printf("\n""\t\t""with haptic");

				// Check if the joystick is already into configuration, if not then add it.
				// This is automatically done by myConfig.
				myConfig.updateInput(SDL_JoystickGetGUID(joystick), new InputJoystick(joystick));
			}
		}

		myConfig.mapInputs();
		myConfig.save();

		printf("\n""[=] InputDevices:");
		for(size_t i = 0; i < InputDevices.size(); i++) {
			printf("\n""\t""%u:", i);
			printf("\n""\t""\t""Deltas:  %u", InputDevices[i]->Deltas.Length);
			printf("\n""\t""\t""Ranges:  %u", InputDevices[i]->Ranges.Length);
			printf("\n""\t""\t""States:  %u", InputDevices[i]->States.Length);
			printf("\n""\t""\t""Buttons: %u", InputDevices[i]->Buttons.Length);
		}

        Serial mySerial("COM3", 33);

		for (size_t i = 0; i < Outputs.size(); i++) mySerial.myOutputs.push_back(Outputs[i]);

        while (1) {
            SDL_Delay(20);

            // TODO Process possible joystick (re)connects (SDL_JoyDeviceEvent ?)
			// like:
			// foreach newly connected joystick i
			// j = open(i)
			// if (j) myConfig.updateInput(SDL_JoystickGetGUID(j), new InputJoystick(j));
			SDL_JoystickUpdate();
            for (size_t i = 0; i < InputDevices.size(); i++) InputDevices[i]->Update();
            
            mySerial.SendOutputs();

            Stack<byte> *TelemData = mySerial.getTelem();
            if (TelemData != nullptr) {
				printf("\n""%03u |", TelemData->Data[0]);
                for (byte i = 1; i < 9; i += 2) printf(" %04umV", (TelemData->Data[i] << 8) | TelemData->Data[i + 1]);
				for (byte i = 13; i < 33; i++) printf(" %03u", TelemData->Data[i]);
                delete TelemData;
            }
        }
		/*
        while (1) {
            SDL_Delay(20);

            SDL_JoystickUpdate();
            for (size_t i = 0; i < InputDevices.size(); i++) InputDevices[i]->Update();

			printf("\n");
			for (size_t i = 0; i < Outputs.size(); i++) printf(" %5u",Outputs[i]->Get());
        }
		*/

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
