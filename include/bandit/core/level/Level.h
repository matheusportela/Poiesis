// Base class for game levels.

#ifndef LEVEL_H_
#define LEVEL_H_

class Level
{
  public:
    Level() : finished(false) {}
    virtual ~Level() {}

    // Executes basic level management in the first frame where the level is
    // executed by game.
    virtual void Start() = 0;

    // Executes level update every frame.
    virtual void Update() = 0;

    // Executes level cleaning up when it is marked to finish.
    virtual void Finish() = 0;

    // Indicates whether the level is finished.
    bool IsFinished() { return finished; }

    // Sets level to finish.
    void SetFinished() { finished = true; }

  private:
    // Flags whether the level must finish.
    bool finished;
};

#endif // LEVEL_H_