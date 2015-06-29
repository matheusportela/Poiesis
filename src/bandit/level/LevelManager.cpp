#include "bandit/level/LevelManager.h"

void LevelManager::SetCurrentLevel(std::shared_ptr<Level> currentLevel)
{
    this->currentLevel = currentLevel;
    newLevel = true;
}

void LevelManager::Update()
{
    LOG_D("[LevelManager] Updating levels");

    if (!currentLevel)
    {
        LOG_W("[LevelManager] No level available");
        return;
    }

    if (newLevel)
    {
        currentLevel->Start();
        newLevel = false;
    }
    else if (currentLevel->IsFinished())
    {
        currentLevel->Finish();
        currentLevel = nullptr;
    }
    else
    {
        currentLevel->Update();
    }
}

bool LevelManager::HasFinished()
{
    return (currentLevel == nullptr);
}