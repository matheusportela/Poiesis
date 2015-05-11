// @file   PenguinsRightRotationCommand.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Turn Penguins's base right.

#ifndef PENGUINS_RIGHT_ROTATION_COMMAND_H_
#define PENGUINS_RIGHT_ROTATION_COMMAND_H_

#include "Command.h"

class Penguins;

class PenguinsRightRotationCommand : public Command
{
  public:
    PenguinsRightRotationCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

#endif // PENGUINS_RIGHT_ROTATION_COMMAND_H_