// Timer for event firing.

#ifndef TIMER_H_
#define TIMER_H_

#include <functional>

class Timer
{
  public:
    Timer();

    // Sets a aperiodic timer that needs to be reset to be used again.
    void SetTime(float timeAmount);

    // Sets a periodic timer that automatically resets after firing.
    void SetPeriod(float period);

    // Sets a callback function that is called once when timer fires.
    void SetCallback(std::function<void()> callback);

    // Calls timer callback.
    void FireCallback();

    // Updates time left.
    void Update(float dt);

    // Checks whether the timer has fired.
    bool HasFired();

  private:
    // Saves the amount of time left before firing the timer.
    float timeLeft;

    bool periodic;
    float period;

    std::function<void()> callback;
    bool firedCallback;
};

#endif // TIMER_H_