#include "poiesis/levels/LoseLevel.h"

void LoseLevel::Start()
{
    auto loseImage = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, Vector(CFG_GETI("WINDOW_WIDTH")/2, 450)), loseImage);
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("LOSE_IMAGE")), loseImage);

    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(880, 700,
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
        std::bind(&LoseLevel::MenuButtonCallback, this));

    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    
    if (CFG_GETB("DEBUG"))
        Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void LoseLevel::Update()
{
}

void LoseLevel::Finish()
{
    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void LoseLevel::MenuButtonCallback()
{
    LOG_I("[LoseLevel] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}