// @file   MenuCommand.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Go to game menu.

#ifndef MENU_COMMAND_H_
#define MENU_COMMAND_H_

#include <memory>

#include "Command.h"

class State;

class MenuCommand : public Command
{
  public:
    MenuCommand(State* state);

    void Execute();

  private:
    // Reference to the Game State that instantiated this command.
    State* state;
};

#endif // MENU_COMMAND_H_