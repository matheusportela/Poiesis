#include "poiesis/systems/AnimationSystem.h"

std::string AnimationSystem::GetName()
{
    return "AnimationSystem";
}

void AnimationSystem::Update(float dt)
{
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("SpriteComponent");
    std::shared_ptr<SpriteComponent> spriteComponent;

    for (auto entity : entities)
    {
        for (auto component : Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent"))
        {
            auto spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
            auto elapsedTime = spriteComponent->GetElapsedTime();
            auto frameDuration = spriteComponent->GetFrameDuration();
            auto currentFrame = spriteComponent->GetCurrentFrame();
            auto repeat = spriteComponent->GetRepeat();
            auto numFrames = spriteComponent->GetNumFrames();

            elapsedTime += dt;

            if (elapsedTime >= frameDuration)
            {
                elapsedTime = 0;
                ++currentFrame;

                if (repeat)
                    currentFrame = currentFrame >= numFrames ? 0 : currentFrame;
                else
                    currentFrame = currentFrame >= numFrames ? numFrames-1 : currentFrame;
            }

            spriteComponent->SetElapsedTime(elapsedTime);
            spriteComponent->SetCurrentFrame(currentFrame);
        }
    }
}