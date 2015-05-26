#include "bandit/entity/SystemManager.h"

void SystemManager::AddSystem(std::shared_ptr<System> system)
{
    LOG_D("[SystemManager] Adding \"" << system->GetName() << "\" system");
    systems.push_back(system);
}

void SystemManager::Update(float dt)
{
    for (std::shared_ptr<System> system : systems)
    {
        LOG_D("[SystemManager] Updating \"" << system->GetName() << "\" system");
        system->Update(dt);
    }
}