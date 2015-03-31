// @file   State.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class implementation

#include "State.h"

State::State()
{
    quitRequested = false;
    bg = new Sprite(CFG_GETP("STATE_BACKGROUND"));
}

State::~State()
{
    if (bg)
        delete bg;
}

void State::Update()
{
    CheckQuitRequested();
}

void State::Render()
{
    bg->Render(0, 0);
}

bool State::IsQuitRequested()
{
    return quitRequested;
}

void State::CheckQuitRequested()
{
    // Verify if either Alt+F4 or close button was pressed.
    if (SDL_QuitRequested())
        quitRequested = true;
}