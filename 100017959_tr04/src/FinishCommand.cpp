// @file   FinishCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Mark game state to finish.

#include "FinishCommand.h"
#include "State.h"

FinishCommand::FinishCommand(State* state) : state(state)
{
}

void FinishCommand::Execute()
{
    state->SetFinished();
}