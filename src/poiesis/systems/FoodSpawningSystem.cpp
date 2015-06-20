#include "poiesis/systems/FoodSpawningSystem.h"

FoodSpawningSystem::FoodSpawningSystem()
{
    timer.SetPeriod(CFG_GETF("FOOD_SPAWNING_PERIOD"));
    timer.SetCallback(std::bind(&FoodSpawningSystem::SpawnFood, this));
}

std::string FoodSpawningSystem::GetName()
{
    return "FoodSpawningSystem";
}

void FoodSpawningSystem::Update(float dt)
{
    timer.Update(dt);
}

void FoodSpawningSystem::SpawnFood()
{
    Random random;
    float foodSpawningChance = CFG_GETF("FOOD_SPAWNING_CHANCE");

    if (random.GenerateFloat() < foodSpawningChance)
    {
        float x = random.GenerateFloat(0, CFG_GETF("WINDOW_WIDTH"));
        float y = random.GenerateFloat(0, CFG_GETF("WINDOW_HEIGHT")); 
        EntityFactory::CreateFood(Vector(x, y));
        LOG_I("[FoodSpawningSystem] Spawning new food at " << x << ", " << y);
    }
}