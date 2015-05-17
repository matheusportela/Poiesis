#include "bandit/core/entity/Entity.h"

unsigned int Entity::lastGeneratedId = 0;

Entity::Entity()
{
    if (lastGeneratedId == std::numeric_limits<unsigned int>::max())
    {
        LOG_E("[Entity] No entity UI available");
        exit(1);
    }

    ++lastGeneratedId;
    id = lastGeneratedId;
}

unsigned int Entity::GetId()
{
    return id;
}