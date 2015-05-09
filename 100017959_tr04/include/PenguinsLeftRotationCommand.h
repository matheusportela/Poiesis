// @file   PenguinsLeftRotationCommand.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Turn Penguins's base left.

#ifndef PENGUINS_LEFT_ROTATION_COMMAND_H_
#define PENGUINS_LEFT_ROTATION_COMMAND_H_

#include "Command.h"

class Penguins;

class PenguinsLeftRotationCommand : public Command
{
  public:
    PenguinsLeftRotationCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

#endif // PENGUINS_LEFT_ROTATION_COMMAND_H_