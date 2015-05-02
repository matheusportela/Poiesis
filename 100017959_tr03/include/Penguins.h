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

#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Vector.h"

// Remove after test
#include "Logger.h"

class Penguins : public GameObject
{
  public:
    // Initializes Penguins in the given position.
    Penguins(Point position);

    // Destroys Penguins.
    ~Penguins();

    // Updates Penguins position after some elapsed time.
    void UpdatePosition(float dt);

    // Runs update cycle.
    void Update(float dt);

    // Renders Penguins.
    void Render();

    // Checks whether Penguins is dead.
    bool IsDead();

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
    int hp;
    float linearAcceleration;
    float angularSpeed;
    float maxLinearSpeed;
    Sprite* bodySprite;
    Sprite* cannonSprite;
};

#endif // PENGUINS_H_