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
#include <vector>

#include "Bullet.h"
#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Point.h"
#include "Sprite.h"
#include "Vector.h"

// Remove after test
#include "Logger.h"

class Penguins : public GameObject
{
  public:
    // Initializes Penguins in the given position.
    Penguins(const Point& position);

    // Destroys Penguins.
    ~Penguins();

    // Updates the cannon rotation to match the mouse.
    void UpdateCannonRotation();

    // Updates Penguins position after some elapsed time.
    void UpdatePosition(float dt);

    // Updates bullets shot by Penguins.
    void UpdateBullets(float dt);

    // Destroy bullets marked as dead.
    void DestroyBullets();

    // Runs update cycle.
    void Update(float dt);

    // Renders bullets that have been shot.
    void RenderBullets();

    // Renders Penguins.
    void Render();

    // Checks whether Penguins is dead.
    bool IsDead();

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
    // Penguins body sprite, placed below the cannon sprite. This is also the
    // sprite considered for positioning and collision.
    Sprite* bodySprite;

    // Penguins cannon sprite, placed above the body sprite. This sprite has
    // independent rotation from the body sprite.
    Sprite* cannonSprite;

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

    // Penguins's bullets.
    std::vector<std::unique_ptr<Bullet>> bulletArray;
};

#endif // PENGUINS_H_