#include "bandit/adapters/sdl/SDLTimerAdapter.h"

SDLTimerAdapter::SDLTimerAdapter()
{
    if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0)
    {
        std::cerr << "[SDLTimerAdapter] Error on initializing SDL timer."
            << SDL_GetError() << std::endl;
    }
}

SDLTimerAdapter::~SDLTimerAdapter()
{
    SDL_QuitSubSystem(SDL_INIT_TIMER);
}

float SDLTimerAdapter::GetElapsedTime()
{
    unsigned int ticks = SDL_GetTicks(); // in milliseconds
    unsigned int milliseconds = ticks - previousTicks;
    float seconds = milliseconds/1000.0;
    previousTicks = ticks;
    return seconds;
}

void SDLTimerAdapter::Sleep(float seconds)
{
    float milliseconds = seconds*1000.0;
    SDL_Delay(milliseconds);
}