#include "poiesis/levels/WinLevel.h"

void WinLevel::Start()
{
    auto winImage = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, Vector(CFG_GETI("WINDOW_WIDTH")/2, 450)), winImage);
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("WIN_IMAGE")), winImage);

    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(880, 700,
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
        std::bind(&WinLevel::MenuButtonCallback, this));

    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    
    if (CFG_GETB("DEBUG"))
        Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void WinLevel::Update()
{
}

void WinLevel::Finish()
{
    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void WinLevel::MenuButtonCallback()
{
    LOG_I("[WinLevel] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}