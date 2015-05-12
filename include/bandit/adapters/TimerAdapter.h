// Interface to timing related methods.

#ifndef TIMER_ADAPTER_H_
#define TIMER_ADAPTER_H_

class TimerAdapter
{
  public:
    virtual ~TimerAdapter() {}

    // Gets the elapsed time since the last invocation of this method, in
    // seconds.
    virtual float GetElapsedTime() = 0;

    // Blocks program execution for the given amount of time, in seconds.
    virtual void Sleep(float seconds) = 0;
};

#endif // TIMER_ADAPTER_H_