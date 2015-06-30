#include "poiesis/levels/WinLevel.h"

void WinLevel::Start()
{
    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(1700, 10, 150, 50),
        std::bind(&WinLevel::MenuButtonCallback, this));

    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void WinLevel::Update()
{
    Engine::GetInstance().GetGraphicsAdapter()->Write("You win",
        CFG_GETP("FONT_FILE"), CFG_GETI("WINDOW_WIDTH")/2,
        CFG_GETI("WINDOW_HEIGHT")/2);
}

void WinLevel::Finish()
{
}

void WinLevel::MenuButtonCallback()
{
    LOG_I("[WinLevel] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}