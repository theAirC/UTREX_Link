
#define ifdie(condition) if (condition) LogDie(#condition);
#define ifdieSDL(SDLcode) if (SDLcode < 0) LogDieSDL(#SDLcode);

void LogDie(const char* msg)
{
    printf("\n""[X] %s", msg);
    exit(EXIT_FAILURE);
}

void LogDieSDL(const char* msg)
{
    printf("\n""[X][SDL] %s", msg);
    printf("\n""    SDL Error: %s", SDL_GetError());
    exit(EXIT_FAILURE);
}
