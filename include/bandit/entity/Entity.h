// Entity is an object with an unique ID number. This allows us to identify any
// system and get its components.

#ifndef ENTITY_H_
#define ENTITY_H_

#include <limits>

#include "bandit/core/Log.h"

class Entity
{
  public:
    Entity();
    virtual ~Entity() {}
    unsigned int GetId();

  private:
    unsigned int id;

    // Tracks the lowest unassigned ID in order to properly generate a new ID
    // when creating a new entity.
    static unsigned int lowestUnassignedId;
};

#endif // ENTITY_H_