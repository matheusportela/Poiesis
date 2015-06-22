// Timer for periodic event firing.

#ifndef PERIODIC_TIMER_H_
#define PERIODIC_TIMER_H_

#include <functional>

#include "bandit/core/time/Timer.h"

class PeriodicTimer
{
  public:
    PeriodicTimer();

    // Sets a periodic timer that automatically resets after firing.
    void SetPeriod(float period);

    // Sets a callback function that is called once when timer fires.
    void SetCallback(std::function<void()> callback);

    // Updates time left.
    void Update(float dt);

  private:
    Timer timer;
    float period;
    std::function<void()> callback;
};

#endif // PERIODIC_TIMER_H_