// @file   TitleState.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Title screen

#include "TitleState.h"

TitleState::TitleState()
{
    bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("TITLE_BACKGROUND")));
    ConfigureInputCommands();
}

void TitleState::ConfigureInputCommands()
{
    quitButtonCommand = CommandFactory::CreateQuitCommand(this,
        InputType::QuitButtonPress);

    quitEscCommand = CommandFactory::CreateQuitCommand(this,
        InputType::KeyPress, KeyboardButton::Esc);
}

void TitleState::Update(float dt)
{

}

void TitleState::Render()
{
    bg->Render(Point(0, 0));
}

void TitleState::Pause()
{

}

void TitleState::Resume()
{

}
