// @file   RetryCommand.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Try the game again.

#ifndef RETRY_COMMAND_H_
#define RETRY_COMMAND_H_

#include <memory>

#include "Command.h"

class State;

class RetryCommand : public Command
{
  public:
    RetryCommand(State* state);

    void Execute();

  private:
    // Reference to the Game State that instantiated this command.
    State* state;
};

#endif // RETRY_COMMAND_H_