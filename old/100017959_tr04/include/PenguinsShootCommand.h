// @file   PenguinsShootCommand.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins shoot in the direction where it's cannon is point to.

#ifndef PENGUINS_SHOOT_COMMAND_H_
#define PENGUINS_SHOOT_COMMAND_H_

#include "Command.h"

class Penguins;

class PenguinsShootCommand : public Command
{
  public:
    PenguinsShootCommand(Penguins* penguins);

    // Execute shoot.
    void Execute();

  private:
    // Reference to the Penguins that instantiated this command.
    Penguins* penguins;
};

#endif // PENGUINS_SHOOT_COMMAND_H_