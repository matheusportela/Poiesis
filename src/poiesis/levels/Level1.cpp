#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    EntityFactory::CreateBackground();
    EntityFactory::CreateCell(1, Vector(250, 250));

    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");
    SetFinished();
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");
}