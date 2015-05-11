// @file   TitleState.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Title screen

#include "TitleState.h"
#include "Game.h"
#include "StageState.h"

TitleState::TitleState()
{
    bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("TITLE_BACKGROUND")));
    ConfigureInputCommands();
    text = std::unique_ptr<Text>(new Text(
        CFG_GETP("TITLE_FONT_FILE"),
        CFG_GETI("TITLE_FONT_SIZE"),
        Text::Blended,
        CFG_GETS("TITLE_TEXT"),
        Text::Black,
        Point(CFG_GETI("TITLE_POSITION_X"), CFG_GETI("TITLE_POSITION_Y"))));
    showText = false;
}

TitleState::~TitleState()
{
    Game::GetInstance()->AddState(std::unique_ptr<State>(new StageState()));
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
    textTimer.Update(dt);

    if (textTimer.IsFinished())
    {
        showText = showText == true ? false : true;
        textTimer.Set(CFG_GETF("TITLE_TEXT_PERIOD"));
    }
}

void TitleState::Render()
{
    bg->Render(Point(0, 0));

    if (showText)
        text->Render();
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
}
