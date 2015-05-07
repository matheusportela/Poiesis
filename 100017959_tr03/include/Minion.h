// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#ifndef MINION_H_
#define MINION_H_

#include <memory>

#include "MinionBullet.h"
#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Logger.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

class Minion : public GameObject
{
  public:
    Minion(GameObject* parent, float arcOffset);

    // Sets minion to die.
    void SetDead();

    // Spawns minion with a random scale factor.
    void SetRandomScale();

    // Updates minion position.
    void UpdatePosition(float dt);

    // Update cycle.
    void Update(float dt);

    // Render cycle.
    void Render();

    // Checks whether the minion must be destroyed.
    bool IsDead();

    // Implements behavior for collision.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "Minion".
    bool Is(std::string type);

    // Shoots a bullet in the direction of the given position.
    void Shoot(const Point& position);

  private:
    // Minion's parent, required to keep tracking the position.
    GameObject* parent;

    // Minion's distance from it's parent.
    float distance;

    // Minion's angular speed to rotate around it's parent.
    float angularSpeed;

    // Minion's position in the circular trajectory around it's parent.
    Vector rotationVector;

    // Flag for Minion death.
    bool dead;
};

#endif // MINION_H_