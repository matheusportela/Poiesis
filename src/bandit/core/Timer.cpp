#include "bandit/core/Timer.h"

Timer::Timer() : timeLeft(0)
{
}

void Timer::SetTime(float timeAmount)
{
    this->timeLeft = timeAmount;
}

void Timer::Update(float dt)
{
    timeLeft = timeLeft > 0 ? timeLeft-dt : 0;
}

bool Timer::HasFired()
{
    return (timeLeft == 0);
}