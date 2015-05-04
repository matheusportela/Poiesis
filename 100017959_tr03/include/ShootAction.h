// @file   ShootAction.h
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Shoots to a target place.

#ifndef SHOOT_ACTION_H_
#define SHOOT_ACTION_H_

#include <memory>
#include <limits>

#include "Action.h"
#include "GameObject.h"
#include "Minion.h"
#include "Point.h"

class ShootAction : public Action
{
  public:
    ShootAction(GameObject *object,
        std::vector<std::shared_ptr<Minion>> minionArray, const Point& target);

    int GetClosestMinion(const Point& point);

    // Moves the game object to the specified point.
    void Execute();

    // Checks whether the object is close enough to the target to consider is
    // has arrived.
    bool IsFinished();

  private:
    // Minion that will shoot.
    std::vector<std::shared_ptr<Minion>> minionArray;

    // Target point to move the object.
    Point target;
};

#endif // SHOOT_ACTION_H_