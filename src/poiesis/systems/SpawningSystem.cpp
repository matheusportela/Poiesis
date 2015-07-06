#include "poiesis/systems/SpawningSystem.h"

SpawningSystem::SpawningSystem(SpawningType spawningType, float spawningChance,
    float spawningPeriod) :
    spawningType(spawningType), spawningChance(spawningChance)
{
    timer.SetPeriod(spawningPeriod);
    timer.SetCallback(std::bind(&SpawningSystem::Spawn, this));
}

std::string SpawningSystem::GetName()
{
    return "SpawningSystem";
}

void SpawningSystem::Update(float dt)
{
    timer.Update(dt);
}

void SpawningSystem::Spawn()
{
    if (random.GenerateFloat() < spawningChance)
    {
        switch (spawningType)
        {
            case CellSpawning:
                SpawnCell();
                break;
            case CellParticleSpawning:
                SpawnCellParticle();
                break;
            case FoodSpawning:
                SpawnFood();
                break;
        }
    }
}

void SpawningSystem::SpawnCell()
{
    float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
    float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT"));
    EntityFactory::CreateRandomCell(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell at " << x << ", " << y);
}

void SpawningSystem::SpawnCellParticle()
{
    float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
    float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT"));
    EntityFactory::CreateCellParticle(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell particle at " << x << ", " << y);
}

void SpawningSystem::SpawnFood()
{
    float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
    float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT")); 
    EntityFactory::CreateFood(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new food at " << x << ", " << y);
}