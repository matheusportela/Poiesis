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
            case Level1CellSpawning:
                SpawnLevel1Cell();
                break;
            case Level2CellSpawning:
                SpawnLevel1Cell();
                break;
            case Level3CellSpawning:
                SpawnLevel1Cell();
                break;
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
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    EntityFactory::CreateCell(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell at " << x << ", " << y);
}

void SpawningSystem::SpawnLevel1Cell()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    auto cell = EntityFactory::CreateCell(Vector(x, y));
    Engine::GetInstance().AddComponent(
        std::make_shared<AIComponent>("EatableComponent"), cell);
    LOG_I("[SpawningSystem] Spawning new level 1 cell at " << x << ", " << y);
}

void SpawningSystem::SpawnLevel2Cell()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    auto cell = EntityFactory::CreateCell(Vector(x, y));
    Engine::GetInstance().AddComponent(
        std::make_shared<AIComponent>("CellParticleComponent"), cell);
    LOG_I("[SpawningSystem] Spawning new level 2 cell at " << x << ", " << y);
}

void SpawningSystem::SpawnLevel3Cell()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    auto cell = EntityFactory::CreateCell(Vector(x, y));
    Engine::GetInstance().AddComponent(
        std::make_shared<AIComponent>("EatableComponent"), cell);
    LOG_I("[SpawningSystem] Spawning new level 3 cell at " << x << ", " << y);
}

void SpawningSystem::SpawnCellParticle()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    EntityFactory::CreateCellParticle(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new cell particle at " << x << ", " << y);
}

void SpawningSystem::SpawnFood()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    EntityFactory::CreateFood(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new food at " << x << ", " << y);
}

void SpawningSystem::SpawnBacterium()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    EntityFactory::CreateBacterium(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new bacterium at " << x << ", " << y);
}

void SpawningSystem::SpawnVirus()
{
    float x = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
    float y = random.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
    EntityFactory::CreateVirus(Vector(x, y));
    LOG_I("[SpawningSystem] Spawning new virus at " << x << ", " << y);
}