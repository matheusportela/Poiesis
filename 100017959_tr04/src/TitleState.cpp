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
    quitCommand = CommandFactory::CreateQuitCommand(this);
    inputManager.RegisterCommand(quitCommand, InputType::QuitButtonPress);
    inputManager.RegisterCommand(quitCommand, InputType::KeyPress,
        KeyboardButton::Esc);

    finishCommand = CommandFactory::CreateFinishCommand(this);
    inputManager.RegisterCommand(finishCommand, InputType::KeyPress,
        KeyboardButton::Space);
}

void TitleState::Update(float dt)
{
    inputManager.ProcessInputs();
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
