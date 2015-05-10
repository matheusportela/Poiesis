// @file   FinishCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Mark game state to finish.

#ifndef FINISH_COMMAND_H_
#define FINISH_COMMAND_H_

#include "Command.h"

class State;

class FinishCommand : public Command
{
  public:
    FinishCommand(State* state);

    void Execute();

  private:
    // Reference to the Game State that instantiated this command.
    State* state;
};

#endif // FINISH_COMMAND_H_