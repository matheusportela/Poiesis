// @file   PenguinsCommands.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief All commands for Penguins.

#ifndef PENGUINS_COMMANDS_H_
#define PENGUINS_COMMANDS_H_

#include "Command.h"

class Penguins;

class PenguinsShootCommand : public Command
{
  public:
    PenguinsShootCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

class PenguinsSpeedUpCommand : public Command
{
  public:
    PenguinsSpeedUpCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

class PenguinsSlowDownCommand : public Command
{
  public:
    PenguinsSlowDownCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

class PenguinsLeftRotationCommand : public Command
{
  public:
    PenguinsLeftRotationCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

class PenguinsRightRotationCommand : public Command
{
  public:
    PenguinsRightRotationCommand(Penguins* penguins);
    void Execute();

  private:
    Penguins* penguins;
};

#endif // PENGUINS_COMMANDS_H_