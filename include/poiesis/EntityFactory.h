// Creates default entities to be used in the game.

#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <memory>

#include "bandit/Engine.h"
#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/CameraFollowComponent.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/EatableComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/SlowingComponent.h"
#include "poiesis/components/SpriteComponent.h"

class EntityFactory
{
  public:
    // Creates background: a single immovable sprite.
    static std::shared_ptr<Entity> CreateBackground();

    // Creates cell: a sprite than can move with user input.
    static std::shared_ptr<Entity> CreateCell(float inverseMass,
        Vector position);

    // Creates player: a cell that is followed by the camera.
    static std::shared_ptr<Entity> CreatePlayer();

    // Creates food: a sprite that can move with user input.
    static std::shared_ptr<Entity> CreateFood(Vector position);

    // Creates camera: a position for rendering images.
    static std::shared_ptr<Entity> CreateCamera();

    // Creates slow area: a region with reduces entities speed.
    static std::shared_ptr<Entity> CreateSlowArea(Vector position);

    // Creates slow area: a region with increases entities speed.
    static std::shared_ptr<Entity> CreateFastArea(Vector position);
};

#endif // ENTITY_FACTORY_H_