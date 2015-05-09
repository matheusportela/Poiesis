// @file   PenguinsSlowDownCommand.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins go slower.

#ifndef PENGUINS_SLOW_DOWN_COMMAND_H_
#define PENGUINS_SLOW_DOWN_COMMAND_H_

#include "Command.h"

class Penguins;

class PenguinsSlowDownCommand : public Command
{
  public:
    PenguinsSlowDownCommand(Penguins* penguins);

    // Makes it goes slower.
    void Execute();

  private:
    // Reference to the Penguins that instantiated this command.
    Penguins* penguins;
};

#endif // PENGUINS_SLOW_DOWN_COMMAND_H_