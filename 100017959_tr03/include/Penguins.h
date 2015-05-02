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

class Penguins : public GameObject
{
  public:
    Penguins(Point position);
    ~Penguins();
    void Update(float dt);
    void Render();
    bool IsDead();
    void Shoot();

  private:
    int hp;
    Sprite* bodySprite;
    Sprite* cannonSprite;
};

#endif // PENGUINS_H_