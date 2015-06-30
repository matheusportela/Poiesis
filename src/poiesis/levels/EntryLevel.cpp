#include "poiesis/levels/EntryLevel.h"

void EntryLevel::Start()
{
    LOG_I("[EntryLevel] Starting");
    
    EntityFactory::CreateButton(CFG_GETP("START_BUTTON_IMAGE"),
        Rectangle(800, 500, 150, 50),
        std::bind(&EntryLevel::StartButtonCallback, this));

    // Creating systems.
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void EntryLevel::Update()
{
}

void EntryLevel::Finish()
{
    LOG_I("[EntryLevel] Finishing");
    Engine::GetInstance().SetNextLevel(std::make_shared<Level1>());
}

void EntryLevel::StartButtonCallback()
{
    LOG_I("[EntryLevel] Clicked on start button");
    SetFinished();
}