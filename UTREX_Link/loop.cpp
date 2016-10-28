
SDL_Event event;

void loop()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_JOYAXISMOTION:
                /* Handle Joystick Motion */
                //if (event.jaxis.axis == 0) printf("%i\n", (event.jaxis.value) >> 5);
                break;

            case SDL_KEYDOWN:
                /* handle keyboard stuff here */
                break;

            case SDL_QUIT:
                /* Set whatever flags are necessary to */
                /* end the main game loop here */
                break;
        }
    }

    SDL_JoystickUpdate();
    for(size_t i = 0; i < InputDevices.size(); i++) {
        InputDevices[i]->Update();
        printf("\n""Ranges:  %d", InputDevices[i]->Ranges[0]);
        printf("\n""States:  %d", InputDevices[i]->States[0]);
    }
    SDL_Delay(100);
}
