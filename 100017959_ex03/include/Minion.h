// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#ifndef MINION_H_
#define MINION_H_

#include <queue>

#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

class Sprite;

class Minion : public GameObject
{
  public:
    Minion(GameObject* parent, float arcOffset);
    ~Minion();

    // Defining GameObject virtual methods.
    void Update(float dt);
    void Render();
    bool IsDead();
    void Shoot(Point position);

  private:
    // Minion's sprite.
    Sprite* sprite;

    GameObject* parent;
    float distance;
    float angularSpeed;
    Vector circumferencePosition;
};

#endif // MINION_H_