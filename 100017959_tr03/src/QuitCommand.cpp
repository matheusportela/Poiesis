// @file   QuitCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Mark game state to quit.

#include "QuitCommand.h"
#include "State.h"

QuitCommand::QuitCommand(State* state) : state(state)
{
}

void QuitCommand::Execute()
{
    state->SetQuitRequested();
}