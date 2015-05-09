// @file   PenguinsLeftRotationCommand.cpp
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Turn Penguins's base left.

#include "PenguinsLeftRotationCommand.h"
#include "Penguins.h"

PenguinsLeftRotationCommand::PenguinsLeftRotationCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsLeftRotationCommand::Execute()
{
    LOG_D("[PenguinsLeftRotationCommand] Execute");
    penguins->LeftRotationCallback();
}