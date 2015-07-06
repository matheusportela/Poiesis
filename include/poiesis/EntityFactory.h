// Creates default entities to be used in the game.

#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <functional>
#include <memory>

#include "bandit/Engine.h"
#include "poiesis/components/AIComponent.h"
#include "poiesis/components/ButtonComponent.h"
#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/CameraFollowComponent.h"
#include "poiesis/components/CellComponent.h"
#include "poiesis/components/CellParticleComponent.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/CombatComponent.h"
#include "poiesis/components/ComplexityComponent.h"
#include "poiesis/components/EatableComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/PlayerComponent.h"
#include "poiesis/components/SlowingComponent.h"
#include "poiesis/components/SpriteComponent.h"
#include "poiesis/components/VitaminComponent.h"

class EntityFactory
{
  public:
    // Creates background: a single immovable sprite.
    static std::shared_ptr<Entity> CreateBackground();

    // Creates cell: a sprite than can move with user input.
    static std::shared_ptr<Entity> CreateCell(std::string image,
        Vector position);
    static std::shared_ptr<Entity> CreateAnimatedCell(std::string image,
        int numFrames, float frameDuration, Vector position);
    static std::shared_ptr<Entity> CreateCell(int type,
        Vector position);
    static std::shared_ptr<Entity> CreateRandomCell(Vector position);

    // Creates player: a cell that is followed by the camera.
    static std::shared_ptr<Entity> CreatePlayer();

    // Creates food: a sprite that can move with user input.
    static std::shared_ptr<Entity> CreateFood(Vector position);

    static std::shared_ptr<Entity> CreateCellParticle(Vector position);

    static std::shared_ptr<Entity> CreateVirus(Vector position);

    // Creates camera: a position for rendering images.
    static std::shared_ptr<Entity> CreateCamera(float height = 1);

    // Creates slow area: a region which reduces entities speed.
    static std::shared_ptr<Entity> CreateSlowArea(Vector position);

    // Creates fast area: a region which increases entities speed.
    static std::shared_ptr<Entity> CreateFastArea(Vector position);

    // Creates vitamin area: a region which increases entities growth.
    static std::shared_ptr<Entity> CreateVitaminArea(Vector position);

    // Creates acid area: a region which decreases entities growth.
    static std::shared_ptr<Entity> CreateAcidArea(Vector position);

    // Creates button: a region which an sprite and responds to clicks.
    static std::shared_ptr<Entity> CreateButton(std::string image,
        Rectangle rectangle, std::function<void()> callback);

  private:
    static std::shared_ptr<Entity> CreateCellWithoutSprite(Vector position);
};

#endif // ENTITY_FACTORY_H_