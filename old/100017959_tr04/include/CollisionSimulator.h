// @file   CollisionSimulator.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Simulates collision detection and reaction between game objects.

#ifndef COLLISION_SIMULATOR_H_
#define COLLISION_SIMULATOR_H_

#include <algorithm>
#include <vector>

#include "GameObject.h"
#include "GameObjectManager.h"
#include "Logger.h"
#include "Point.h"
#include "Vector.h"

class CollisionSimulator
{
  public:
    // Collide game objects.
    static void Collide();

    // Checks whether two objects are colliding. Uses Separating Axis Theorem.
    static bool IsColliding(std::shared_ptr<GameObject> object1,
        std::shared_ptr<GameObject> object2);

  private:
    static float Mag(const Point& p);
    
    static Point Norm(const Point& p);

    static float Dot(const Point& a, const Point& b);

    static Point Rotate(const Point& p, float angle);
};

#endif // COLLISION_SIMULATOR_H_