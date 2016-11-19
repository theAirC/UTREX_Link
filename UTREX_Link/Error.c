
#define ifdie(condition) if (condition) LogDie(#condition);
#define ifdieSDL(SDLcode) if (SDLcode < 0) LogDieSDL(#SDLcode);

void LogDie(const char *msg)
{
    printf("\n""[X] %s""\n", msg);
    exit(EXIT_FAILURE);
}

void LogDieSDL(const char *msg)
{
    printf("\n""[X][SDL] %s", msg);
    printf("\n""    SDL Error: %s""\n", SDL_GetError());
    exit(EXIT_FAILURE);
}
