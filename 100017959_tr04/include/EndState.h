// @file   EndState.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Final level

#ifndef END_STATE_H_
#define END_STATE_H_

#include <memory>

#include "Command.h"
#include "CommandFactory.h"
#include "ConfigParser.h"
#include "InputManager.h"
#include "Music.h"
#include "Point.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"

class EndState : public State
{
  public:
    EndState(bool victory);
    ~EndState();
    void ConfigureInputCommands();
    void Update(float dt);
    void Render();
    void Pause();
    void Resume();

  private:
    std::unique_ptr<Sprite> bg;
    std::unique_ptr<Music> music;
    std::unique_ptr<Text> instruction;

    std::shared_ptr<Command> quitCommand;
    std::shared_ptr<Command> retryCommand;
    std::shared_ptr<Command> menuCommand;

    InputManager inputManager;
};

#endif // END_STATE_H_