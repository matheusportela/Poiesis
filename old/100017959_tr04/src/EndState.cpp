// @file   EndState.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Final level

#include "EndState.h"

EndState::EndState(bool victory)
{
    if (victory)
    {
        bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("WIN_BACKGROUND")));
        music = std::unique_ptr<Music>(new Music(CFG_GETP("WIN_MUSIC")));
    }
    else
    {
        bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("LOSE_BACKGROUND")));
        music = std::unique_ptr<Music>(new Music(CFG_GETP("LOSE_MUSIC")));
    }

    instruction = std::unique_ptr<Text>(new Text(
        CFG_GETP("END_FONT_FILE"),
        CFG_GETI("END_FONT_SIZE"),
        Text::Blended,
        CFG_GETS("END_TEXT"),
        Text::Black,
        Point(CFG_GETI("END_TEXT_POSITION_X"),
            CFG_GETI("END_TEXT_POSITION_Y"))));

    music->Play();

    ConfigureInputCommands();
}

EndState::~EndState()
{
    music->Stop();
}

void EndState::ConfigureInputCommands()
{
    quitCommand = CommandFactory::CreateQuitCommand(this);
    inputManager.RegisterCommand(quitCommand, InputType::QuitButtonPress);

    retryCommand = CommandFactory::CreateRetryCommand(this);
    inputManager.RegisterCommand(retryCommand, InputType::KeyPress,
        KeyboardButton::Space);

    menuCommand = CommandFactory::CreateMenuCommand(this);
    inputManager.RegisterCommand(menuCommand, InputType::KeyPress,
        KeyboardButton::Esc);
}

void EndState::Update(float dt)
{
    inputManager.ProcessInputs();
}

void EndState::Render()
{
    bg->Render(Point(0, 0));
    instruction->Render();
}

void EndState::Pause()
{
}

void EndState::Resume()
{
}
