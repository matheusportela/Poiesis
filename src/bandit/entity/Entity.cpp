#include "bandit/entity/Entity.h"

unsigned int Entity::lowestUnassignedId = 0;

Entity::Entity()
{
    if (lowestUnassignedId == std::numeric_limits<unsigned int>::max())
    {
        LOG_E("[Entity] No entity UI available");
        exit(1);
    }

    id = lowestUnassignedId;
    ++lowestUnassignedId;
}

unsigned int Entity::GetId()
{
    return id;
}