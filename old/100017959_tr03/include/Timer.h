// @file   Timer.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Time counter to simulate time passing.

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
  public:
    Timer();

    // Updates time left.
    void Update(float dt);

    // Sets timer with the given time.
    void Set(float time);

    // Checks whether timer has finished.
    bool IsFinished();

  private:
    // Amount of time left before the timer is finished.
    float timeLeft;
};

#endif // TIMER_H_