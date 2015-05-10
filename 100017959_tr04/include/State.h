// @file   State.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Base class for game states

#ifndef STATE_H_
#define STATE_H_

class State
{
  public:
    State() : finished(false), quitRequested(false) {};
    virtual ~State() {};

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    void SetFinished() { finished = true; }
    bool IsFinished() { return finished; }

    void SetQuitRequested() { quitRequested = true; }
    bool IsQuitRequested() { return quitRequested; }

  protected:
    // Defines whether the current state has finished.
    bool finished;

    // Defines whether the user requested to quit from the game.
    bool quitRequested;
};

#endif // STATE_H_