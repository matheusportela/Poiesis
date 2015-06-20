#include "bandit/core/time/Timer.h"

Timer::Timer() : timeLeft(0), periodic(false), period(0), firedCallback(true)
{
}

void Timer::SetTime(float timeAmount)
{
    this->timeLeft = timeAmount;
    firedCallback = false;
}

void Timer::SetPeriod(float period)
{
    this->period = period;
    periodic = true;
    SetTime(period);
}

void Timer::SetCallback(std::function<void()> callback)
{
    this->callback = callback;
    firedCallback = false;
}

void Timer::FireCallback()
{
    firedCallback = true;
    callback();
}

void Timer::Update(float dt)
{
    timeLeft = timeLeft-dt > 0 ? timeLeft-dt : 0;

    if (HasFired() and (!firedCallback))
    {
        FireCallback();

        if (periodic)
            SetTime(period);
    }
}

bool Timer::HasFired()
{
    return (timeLeft == 0);
}