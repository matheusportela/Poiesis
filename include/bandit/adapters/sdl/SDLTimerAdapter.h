// Implementation of TimerAdapter interface using SDL.

#ifndef SDL_TIMER_ADAPTER_H_
#define SDL_TIMER_ADAPTER_H_

#include <iostream>

#include <SDL.h>

#include "bandit/adapters/TimerAdapter.h"

class SDLTimerAdapter : public TimerAdapter
{
  public:
    SDLTimerAdapter();
    ~SDLTimerAdapter();
    float GetElapsedTime();
    void Sleep(float seconds);

  private:
    // Stores the ticks counting for the last calling of GetElapsedTime.
    unsigned int previousTicks;
};

#endif // SDL_TIMER_ADAPTER_H_