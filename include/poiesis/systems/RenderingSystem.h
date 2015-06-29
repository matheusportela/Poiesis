// Process entities with renderable components and render sprites.

#ifndef RENDERING_SYSTEM_H_
#define RENDERING_SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/Engine.h"

#include "poiesis/components/ButtonComponent.h"
#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/SpriteComponent.h"

class RenderingSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    Vector CalculateScreenOffset();
    Vector CalculateCameraOffset();
    void RenderParticle(std::shared_ptr<Entity> entity, Vector cameraOffset,
        Vector cameraPosition);
    void RenderGUI(std::shared_ptr<Entity> entity);
    void RenderSprite(std::shared_ptr<Entity> entity,
        std::shared_ptr<SpriteComponent> spriteComponent, Vector position);
};

#endif // RENDERING_SYSTEM_H_