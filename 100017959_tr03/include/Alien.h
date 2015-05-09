// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#ifndef ALIEN_H_
#define ALIEN_H_

#include <memory>
#include <vector>

#include "AnimatedSprite.h"
#include "ActionScheduler.h"
#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Minion.h"
#include "MoveAction.h"
#include "ShootAction.h"
#include "Sprite.h"
#include "Point.h"
#include "Timer.h"
#include "Vector.h"

class Alien : public GameObject
{
  public:
    // Initializes Alien at the given (x, y) coordinates with a number of
    // minions.
    Alien(const Point& position, int numMinions);

    // Create all it's minions.
    void InitializeMinions(int numMinions);

    // Executes behaviors depending on the current Alien state.
    void RunBehavior();

    // Updates Alien's rotation.
    void UpdateRotation(float dt);

    // Updates Alien's position.
    void UpdatePosition(float dt);

    // Defining GameObject virtual methods.
    void Update(float dt);

    // Renders Alien's sprite.
    void Render();

    // Creates animation used for explosion.
    void CreateExplosionAnimation();

    // Shows explosion sprite.
    void OnDeath();

    // Checks whether Alien's HP is zero.
    bool IsDead();

    // Receives damage from bullets.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "Alien".
    bool Is(std::string type);

    // Moves Alien to the clicked position.
    void MoveBehavior();

    // Makes a minion shoot at the player.
    void ShootBehavior();

    // Makes the Alien rest for a pre-configured amount of time.
    void RestBehavior();

  private:
    enum State
    {
        MOVING,
        SHOOTING,
        RESTING
    };

    // Holds action state for the Alien.
    int behaviorState;

    // Aliens's hitpoints.
    int hp;

    // Alien's rotation vector.
    float angularSpeed;
    Vector rotationVector;

    // Scheduller to deal with sequential actions.
    ActionScheduler actionScheduler;

    // Time between shoots.
    Timer shootCooldown;

    // Alien's minions references, used with ShootAction.
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif // ALIEN_H_