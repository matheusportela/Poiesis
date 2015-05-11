// @file   Penguins.h
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Playable game object.
//
// Penguins is the game object playable by the user. It consists of two
// elements: a bottom penguin, that slides over the ice, and a top penguin,
// that shoots against enemies.
// The user uses the keyboard (W, A, S and D keys) to guide the botton penguin
// across the environment while the top penguin follows the mouse position and
// shoots when the user clicks.
// Penguins die when it's HP is reduced to zero or less.

#ifndef PENGUINS_H_
#define PENGUINS_H_

#include <memory>

#include "Camera.h"
#include "Command.h"
#include "CommandFactory.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Point.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include "Timer.h"
#include "Vector.h"

class Penguins : public GameObject
{
  public:
    // Initializes Penguins in the given position.
    Penguins(const Point& position);

    // Configures all commands accepted by Penguins.
    void ConfigureInputCommands();

    // Simulates friction to slow down penguin when no input is given.
    void ApplyFriction();

    // Avoids Penguins going out of the screen.
    Point CalculateLimitedPosition(const Point& position);

    // Updates the cannon rotation to match the mouse.
    void UpdateCannonRotation();

    // Updates Penguins position after some elapsed time.
    void UpdatePosition(float dt);

    // Runs update cycle.
    void Update(float dt);

    // Renders top penguin cannon sprite.
    void RenderCannonSprite();

    // Renders Penguins.
    void Render();

    // Creates animation used for explosion.
    void CreateExplosionAnimation();

    // Shows explosion sprite.
    void OnDeath();

    // Checks whether Penguins is dead.
    bool IsDead();

    // Implements behavior for collision.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "Penguins".
    bool Is(std::string type);

    // Calculates the bullet initial position, considering the cannon sprite
    // offset.
    Point CalculateBulletPosition();

    // Shoots in the current mouse position.
    void Shoot();

    // Changes Penguins speed given an acceleration.
    void ChangeSpeed(float acceleration);

    // Increases Penguins speed.
    void SpeedUpCallback();

    // Decreases Penguins speed.
    void SlowDownCallback();

    // Turns Penguins to the left.
    void LeftRotationCallback();

    // Turns Penguins to the right.
    void RightRotationCallback();

  private:
    // Penguins cannon sprite, placed above the body sprite. This sprite has
    // independent rotation from the body sprite.
    std::unique_ptr<Sprite> cannonSprite;

    // Penguins HP before death.
    int hp;

    // Penguins linear acceleration, applied by user input.
    float linearAcceleration;

    // Penguins angular speed, applied by user input.
    float angularSpeed;

    // Penguins maximum linear speed.
    float maxLinearSpeed;

    // Cannon current rotation, which is applied to the sprite.
    float cannonRotation;

    // Cooldown for shooting action.
    Timer shootCooldownTimer;

    // Commands.
    std::shared_ptr<Command> shootCommand;
    std::shared_ptr<Command> speedUpCommand;
    std::shared_ptr<Command> slowDownCommand;
    std::shared_ptr<Command> leftRotationCommand;
    std::shared_ptr<Command> rightRotationCommand;

    std::unique_ptr<SoundEffect> explosionSoundEffect;
};

#endif // PENGUINS_H_