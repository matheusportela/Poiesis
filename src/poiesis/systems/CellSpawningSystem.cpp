#include "poiesis/systems/CellSpawningSystem.h"

std::string CellSpawningSystem::GetName()
{
    return "CellSpawningSystem";
}

void CellSpawningSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CellSpawningSystem] Update: " << dt);

    Random random;
    float cellSpawningChance = CFG_GETF("CELL_SPAWNING_CHANCE");

    accumulatedTime += dt;

    if (accumulatedTime > CFG_GETF("CELL_SPAWNING_PERIOD")
        && random.GenerateFloat() < cellSpawningChance)
    {
        accumulatedTime = 0;
        float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
        float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT")); 
        EntityFactory::CreateCell(1, Vector(x, y));
        LOG_I("[CellSpawningSystem] Spawning new cell at " << x << ", " << y);
    }
}