// @file   PenguinsSpeedUpCommand.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins go faster.

#ifndef PENGUINS_SPEED_UP_COMMAND_H_
#define PENGUINS_SPEED_UP_COMMAND_H_

#include "Command.h"

class Penguins;

class PenguinsSpeedUpCommand : public Command
{
  public:
    PenguinsSpeedUpCommand(Penguins* penguins);

    // Makes it goes faster.
    void Execute();

  private:
    // Reference to the Penguins that instantiated this command.
    Penguins* penguins;
};

#endif // PENGUINS_SPEED_UP_COMMAND_H_