// @file   TitleState.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Title screen
//
// Entry point for the game. Shows the splash screen and accepts space bar to
// start the game.

#ifndef TITLE_STATE_H_
#define TITLE_STATE_H_

#include <memory>

#include "Command.h"
#include "CommandFactory.h"
#include "ConfigParser.h"
#include "InputManager.h"
#include "Sprite.h"
#include "State.h"

class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();
    void ConfigureInputCommands();
    void Update(float dt);
    void Render();
    void Pause();
    void Resume();

  private:
    std::unique_ptr<Sprite> bg;

    std::shared_ptr<Command> quitCommand;
    std::shared_ptr<Command> finishCommand;

    InputManager inputManager;
};

#endif // TITLE_STATE_H_