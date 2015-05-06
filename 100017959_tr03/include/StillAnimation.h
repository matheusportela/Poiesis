// @file   StillAnimation.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Animation that stands in place.

#ifndef STILL_ANIMATION_H_
#define STILL_ANIMATION_H_

#include <memory>
#include <string>

#include "AnimatedSprite.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class StillAnimation : public GameObject
{
  public:
    // Initializes animation with a position, a file containing the sprites and
    // a time duration. 
    StillAnimation(const Point& position,
        std::unique_ptr<Sprite> animatedSprite, float time);

    // Updates the animation.
    void UpdateAnimation(float dt);

    // Updates the game object.
    void Update(float dt);

    // Renders animation.
    void Render();

    // Checks whether the animation time has finished.
    bool IsDead();

    // Ignores all collisions.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "StillAnimation".
    bool Is(std::string type);

  private:
    // Timer to countdown the animation period.
    Timer timer;
};

#endif // STILL_ANIMATION_H_