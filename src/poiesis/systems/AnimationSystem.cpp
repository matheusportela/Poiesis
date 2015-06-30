#include "poiesis/systems/AnimationSystem.h"

std::string AnimationSystem::GetName()
{
    return "AnimationSystem";
}

void AnimationSystem::Update(float dt)
{
    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("AnimationComponent");

    for (auto entity : entities)
    {
        auto animationComponent = std::static_pointer_cast<AnimationComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "AnimationComponent"));
        auto elapsedTime = animationComponent->GetElapsedTime();
        auto frameDuration = animationComponent->GetFrameDuration();
        auto currentFrame = animationComponent->GetCurrentFrame();
        auto repeat = animationComponent->GetRepeat();
        auto numFrames = animationComponent->GetNumFrames();

        elapsedTime += dt;

        if (elapsedTime > frameDuration)
        {
            elapsedTime = 0;
            ++currentFrame;

            if (repeat)
                currentFrame = currentFrame == numFrames ? 0 : currentFrame;
            else
                currentFrame = currentFrame == numFrames ? currentFrame-1 : currentFrame;
        }

        animationComponent->SetElapsedTime(elapsedTime);
        animationComponent->SetCurrentFrame(currentFrame);
    }
}