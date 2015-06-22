#include "bandit/core/time/PeriodicTimer.h"

PeriodicTimer::PeriodicTimer() : period(0)
{
}

void PeriodicTimer::SetPeriod(float period)
{
    this->period = period;
    timer.SetTime(period);
}

void PeriodicTimer::SetCallback(std::function<void()> callback)
{
    this->callback = callback;
}

void PeriodicTimer::Update(float dt)
{
    timer.Update(dt);

    if (timer.HasFired())
    {
        if (callback)
            callback();

        timer.SetTime(period);
    }
}