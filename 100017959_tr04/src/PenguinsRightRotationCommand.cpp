// @file   PenguinsRightRotationCommand.cpp
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Turn Penguins's base right.

#include "PenguinsRightRotationCommand.h"
#include "Penguins.h"

PenguinsRightRotationCommand::PenguinsRightRotationCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsRightRotationCommand::Execute()
{
    LOG_D("[PenguinsRightRotationCommand] Execute");
    penguins->RightRotationCallback();
}   Penguins* penguins;