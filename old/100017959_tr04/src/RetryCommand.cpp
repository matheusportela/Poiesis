// @file   RetryCommand.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Try the game again.

#include "RetryCommand.h"
#include "Game.h"
#include "StageState.h"

RetryCommand::RetryCommand(State* state) : state(state)
{
}

void RetryCommand::Execute()
{
    state->SetFinished();
    Game::GetInstance()->AddState(std::unique_ptr<State>(new StageState()));
}