// Timer for event firing.

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
  public:
    Timer();

    // Sets a aperiodic timer that needs to be reset to be used again.
    void SetTime(float timeAmount);

    // Updates time left.
    void Update(float dt);

    // Checks whether the timer has fired.
    bool HasFired();

  private:
    // Saves the amount of time left before firing the timer.
    float timeLeft;
};

#endif // TIMER_H_