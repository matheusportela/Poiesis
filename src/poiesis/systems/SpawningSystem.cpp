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
            case BacteriumSpawning:
                SpawnBacterium();
                break;
            case VirusSpawning:
                SpawnVirus();
                break;
        }
    }
}

void SpawningSystem::SpawnCell()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_MIN_X"), CFG_GETF("LEVEL_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_MIN_Y"), CFG_GETF("LEVEL_MAX_Y"));
    EntityFactory::CreateCell(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell at " << x << ", " << y);
}

void SpawningSystem::SpawnCellParticle()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_MIN_X"), CFG_GETF("LEVEL_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_MIN_Y"), CFG_GETF("LEVEL_MAX_Y"));
    EntityFactory::CreateCellParticle(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell particle at " << x << ", " << y);
}

void SpawningSystem::SpawnFood()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_MIN_X"), CFG_GETF("LEVEL_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_MIN_Y"), CFG_GETF("LEVEL_MAX_Y"));
    EntityFactory::CreateFood(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new food at " << x << ", " << y);
}

void SpawningSystem::SpawnBacterium()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_MIN_X"), CFG_GETF("LEVEL_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_MIN_Y"), CFG_GETF("LEVEL_MAX_Y"));
    EntityFactory::CreateBacterium(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new bacterium at " << x << ", " << y);
}

void SpawningSystem::SpawnVirus()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_MIN_X"), CFG_GETF("LEVEL_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_MIN_Y"), CFG_GETF("LEVEL_MAX_Y"));
    EntityFactory::CreateVirus(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new virus at " << x << ", " << y);
}