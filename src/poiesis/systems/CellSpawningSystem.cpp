#include "poiesis/systems/CellSpawningSystem.h"

CellSpawningSystem::CellSpawningSystem()
{
    timer.SetPeriod(CFG_GETF("CELL_SPAWNING_PERIOD"));
    timer.SetCallback(std::bind(&CellSpawningSystem::SpawnCell, this));
}

std::string CellSpawningSystem::GetName()
{
    return "CellSpawningSystem";
}

void CellSpawningSystem::Update(float dt)
{
    timer.Update(dt);
}

void CellSpawningSystem::SpawnCell()
{
    Random random;
    float cellSpawningChance = CFG_GETF("CELL_SPAWNING_CHANCE");

    if (random.GenerateFloat() < cellSpawningChance)
    {
        float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
        float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT")); 
        EntityFactory::CreateCell(1, Vector(x, y));
        LOG_I("[CellSpawningSystem] Spawning new cell at " << x << ", " << y);
    }
}