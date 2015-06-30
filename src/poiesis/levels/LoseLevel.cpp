#include "poiesis/levels/LoseLevel.h"

void LoseLevel::Start()
{
    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(1700, 10, 150, 50),
        std::bind(&LoseLevel::MenuButtonCallback, this));

    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void LoseLevel::Update()
{
    Engine::GetInstance().GetGraphicsAdapter()->Write("You lose",
        CFG_GETP("FONT_FILE"), CFG_GETI("WINDOW_WIDTH")/2,
        CFG_GETI("WINDOW_HEIGHT")/2);
}

void LoseLevel::Finish()
{
}

void LoseLevel::MenuButtonCallback()
{
    LOG_I("[LoseLevel] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}