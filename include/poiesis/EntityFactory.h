// Creates default entities to be used in the game.

#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <memory>

#include "bandit/Engine.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/EatableComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/SpriteComponent.h"
#include "poiesis/components/ParticleComponent.h"

class EntityFactory
{
  public:
    // Creates background: a single immovable sprite.
    static std::shared_ptr<Entity> CreateBackground();

    // Creates cell: a sprite than can move with user input.
    static std::shared_ptr<Entity> CreateCell(float inverseMass,
        Vector position);

    // Creates food: a sprite that can mvoe with user input.
    static std::shared_ptr<Entity> CreateFood(Vector position);
};

#endif // ENTITY_FACTORY_H_