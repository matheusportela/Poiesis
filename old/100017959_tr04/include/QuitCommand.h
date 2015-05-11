// @file   QuitCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Mark game state to quit.

#ifndef QUIT_COMMAND_H_
#define QUIT_COMMAND_H_

#include "Command.h"

class State;

class QuitCommand : public Command
{
  public:
    QuitCommand(State* state);

    void Execute();

  private:
    // Reference to the Game State that instantiated this command.
    State* state;
};

#endif // QUIT_COMMAND_H_