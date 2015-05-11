// @file   MenuCommand.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Go to game menu.

#include "MenuCommand.h"
#include "Game.h"
#include "TitleState.h"

MenuCommand::MenuCommand(State* state) : state(state)
{
}

void MenuCommand::Execute()
{
    state->SetFinished();
    Game::GetInstance()->AddState(std::unique_ptr<State>(new TitleState()));
}