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

#include "MoveAction.h"
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
    Alien(Point point, int numMinions);
    ~Alien();

    // Create all it's minions.
    void InitializeMinions(int numMinions);

    // Executes queued action.
    void ExecuteAction();

    // Updates Alien's rotation.
    void UpdateRotation(float dt);

    // Updates Alien's position.
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

    // Schedules an action to be execute whenever possible.
    // void ScheduleAction(Action action);

    // Schedules a move action.
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

    // Alien's rotation vector.
    float angularSpeed;
    Vector rotationVector;

    // Actions to be executed by Alien.
    std::queue<std::shared_ptr<Action>> taskQueue;

    // Alien's minions.
    std::vector<std::unique_ptr<Minion>> minionArray;
};

#endif // ALIEN_H_