#include "poiesis/systems/FoodSpawningSystem.h"

std::string FoodSpawningSystem::GetName()
{
    return "FoodSpawningSystem";
}

void FoodSpawningSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[FoodSpawningSystem] Update: " << dt);

    Random random;
    float foodSpawningChance = CFG_GETF("FOOD_SPAWNING_CHANCE");

    accumulatedTime += dt;

    if (accumulatedTime > 5 && random.GenerateFloat() < foodSpawningChance)
    {
        accumulatedTime = 0;
        float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
        float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT")); 
        EntityFactory::CreateFood(Vector(x, y));
        LOG_I("[FoodSpawningSystem] Spawning new food at " << x << ", " << y);
    }
}