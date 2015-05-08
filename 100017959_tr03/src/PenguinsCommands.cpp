#include "PenguinsCommands.h"
#include "Penguins.h"

PenguinsShootCommand::PenguinsShootCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsShootCommand::Execute()
{
    LOG_D("[PenguinsShootCommand] Execute");
    penguins->Shoot();
}

PenguinsSpeedUpCommand::PenguinsSpeedUpCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsSpeedUpCommand::Execute()
{
    LOG_D("[PenguinsSpeedUpCommand] Execute");
    penguins->SpeedUpCallback();
}

PenguinsSlowDownCommand::PenguinsSlowDownCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsSlowDownCommand::Execute()
{
    LOG_D("[PenguinsSlowDownCommand] Execute");
    penguins->SlowDownCallback();
}

PenguinsLeftRotationCommand::PenguinsLeftRotationCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsLeftRotationCommand::Execute()
{
    LOG_D("[PenguinsLeftRotationCommand] Execute");
    penguins->LeftRotationCallback();
}

PenguinsRightRotationCommand::PenguinsRightRotationCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsRightRotationCommand::Execute()
{
    LOG_D("[PenguinsRightRotationCommand] Execute");
    penguins->RightRotationCallback();
}   Penguins* penguins;