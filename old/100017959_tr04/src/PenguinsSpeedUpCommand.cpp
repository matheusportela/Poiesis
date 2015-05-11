// @file   PenguinsSpeedUpCommand.cpp
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins go faster.

#include "PenguinsSpeedUpCommand.h"
#include "Penguins.h"

PenguinsSpeedUpCommand::PenguinsSpeedUpCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsSpeedUpCommand::Execute()
{
    LOG_D("[PenguinsSpeedUpCommand] Execute");
    penguins->SpeedUpCallback();
}