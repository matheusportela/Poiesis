// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#ifndef ALIEN_H_
#define ALIEN_H_

#include <memory>
#include <queue>

#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "Minion.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

class Minion;
class Sprite;

class Alien : public GameObject
{
  public:
    // Initializes Alien at the given (x, y) coordinates with a number of
    // minions.
    Alien(Point& point, int numMinions);
    ~Alien();

    // Create all it's minions.
    void InitializeMinions(int numMinions);

    // Defining GameObject virtual methods.
    void Update(float dt);
    void RenderMinions();
    void Render();
    bool IsDead();

    // Makes a minion shoot with user input.
    void ShootCallback();

  private:
    class Action
    {
      public:
        enum ActionType
        {
            Move,
            Shoot,
        };

        Action(ActionType type, Point& point) : type(type), position(point) {};

        ActionType type;
        Point position;
    };

    // Aliens's hitpoints.
    int hp;

    // Alien's sprite.
    Sprite* sprite;

    // Alien's speed.
    Vector speed;

    // Actions to be executed by Alien.
    std::queue<Action> taskQueue;

    // Alien's minions.
    std::vector<std::unique_ptr<Minion>> minionArray;
};

#endif // ALIEN_H_