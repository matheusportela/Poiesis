// @file   Timer.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Time counter to simulate time passing.

#include "Timer.h"

Timer::Timer() : timeLeft(0)
{
}

void Timer::Update(float dt)
{
    timeLeft = timeLeft > 0 ? timeLeft-dt : 0;
}

void Timer::Set(float timeAmount)
{
    timeLeft = timeAmount;
}

bool Timer::IsFinished()
{
    return (timeLeft == 0);
}