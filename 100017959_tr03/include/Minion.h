// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#ifndef MINION_H_
#define MINION_H_

#include <memory>
#include <vector>

#include "Bullet.h"
#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "Logger.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

class Minion : public GameObject
{
  public:
    Minion(GameObject* parent, float arcOffset);
    ~Minion();

    // Spawns minion with a random scale factor.
    void SetRandomScale();

    // Updates minion position.
    void UpdatePosition(float dt);

    // Updates minion's bullets positions.
    void UpdateBullets(float dt);

    // Destroys bullets.
    void DestroyBullets();

    // Update cycle.
    void Update(float dt);

    // Renders minion's bullets.
    void RenderBullets();

    // Render cycle.
    void Render();

    // Checks whether the minion must be destroyed.
    bool IsDead();

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
    
    // Minion's bullets.
    std::vector<std::unique_ptr<Bullet>> bulletArray;
};

#endif // MINION_H_