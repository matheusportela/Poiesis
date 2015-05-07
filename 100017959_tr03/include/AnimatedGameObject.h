// @file   AnimatedGameObject.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Abstract class for every object which contains an animated sprite.

#ifndef ANIMATED_GAME_OBJECT_H_
#define ANIMATED_GAME_OBJECT_H_

#include <memory>
#include <string>

#include "AnimatedSprite.h"
#include "GameObject.h"
#include "Sprite.h"

class AnimatedGameObject : public GameObject
{
  public:
    AnimatedGameObject(std::string sprite, int numFrames, float frameDuration);

    virtual ~AnimatedGameObject() {}

    void InitializeAnimatedSprite(std::string sprite, int numFrames,
        int frameDuration);

    virtual void Update(float dt);

    void UpdateAnimation(float dt);

    virtual void Render();
};

#endif // ANIMATED_GAME_OBJECT_H_