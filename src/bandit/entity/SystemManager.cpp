#include "bandit/entity/SystemManager.h"

void SystemManager::AddSystem(std::shared_ptr<System> system)
{
    LOG_D("[SystemManager] Adding \"" << system->GetName() << "\" system");
    systems.push_back(system);
}

void SystemManager::DeleteSystem(std::string name)
{
    LOG_D("[SystemManager] Deleting \"" << name << "\" system");
    
    for (unsigned int i = 0; i < systems.size(); ++i)
    {
        if (name == systems[i]->GetName())
        {
            systems.erase(systems.begin() + i);
            --i; // Decrease index since systems is one size smaller
        }
    }
}

void SystemManager::Update(float dt)
{
    std::shared_ptr<System> system;

    for (unsigned int i = 0; i < systems.size(); ++i)
    {
        system = systems[i];
        LOG_D("[SystemManager] Updating \"" << system->GetName() << "\" system");
        system->Update(dt);
    }
}

void SystemManager::Clear()
{
    systems.clear();
}