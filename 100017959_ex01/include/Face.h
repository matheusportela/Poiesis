// @file   Face.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Enemy game object

#ifndef FACE_H_
#define FACE_H_

#include "Config.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Point.h"

class Sprite;

class Face : public GameObject
{
  public:
    // Initializes Face at the given (x, y) coordinates.
    Face(Point& point);
    ~Face();

    // Defining GameObject virtual methods.
    void Update(float dt);
    void Render();
    bool IsDead();

    // Damages by reducing Face's HP.
    void Damage(int damage);

  private:
    // Face's hitpoints.
    int hp;

    // Face's sprite.
    Sprite* sprite;
};

#endif // FACE_H_