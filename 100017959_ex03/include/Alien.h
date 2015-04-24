// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#ifndef ALIEN_H_
#define ALIEN_H_

#include <limits>
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
    class Action;

    // Initializes Alien at the given (x, y) coordinates with a number of
    // minions.
    Alien(Point point, int numMinions);
    ~Alien();

    // Create all it's minions.
    void InitializeMinions(int numMinions);

    // Updates Alien's rotation.
    void UpdateRotation(float dt);

    void UpdatePosition(float dt);

    // Updates minions.
    void UpdateMinions(float dt);

    // Defining GameObject virtual methods.
    void Update(float dt);
    void RenderMinions();
    void Render();
    bool IsDead();

    // Returns the index of the closest minion to a given point.
    int GetClosestMinion(Point point);

    void ScheduleAction(Action action);
    void ScheduleMoveAction(Point point);

    // Moves Alien to the clicked position.
    void MoveCallback();

    // Makes a minion shoot with user input.
    void ShootCallback();

  private:

    // Aliens's hitpoints.
    int hp;

    // Alien's sprite.
    Sprite* sprite;

    // Alien's speed.
    Vector speed;

    // Alien's rotation vector.
    float angularSpeed;
    Vector rotationVector;

    // Actions to be executed by Alien.
    std::queue<Action> taskQueue;

    // Alien's minions.
    std::vector<std::unique_ptr<Minion>> minionArray;
};

class Alien::Action
{
  public:
    enum ActionType
    {
        Move,
        Shoot,
    };

    Action(ActionType type, Point point) : type(type), point(point) {};

    ActionType type;
    Point point;
};

#endif // ALIEN_H_