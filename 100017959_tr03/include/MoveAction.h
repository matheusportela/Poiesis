// @file   MoveAction.h
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Moves a game object to a target point.

#ifndef MOVE_ACTION_H_
#define MOVE_ACTION_H_

#include "Action.h"
#include "GameObject.h"
#include "Point.h"
#include "Vector.h"

class MoveAction : public Action
{
  public:
    MoveAction(GameObject* object, Point target, float speed, float margin);

    // Calculates the displacement from the object current position to the
    // target point.
    Vector CalculateDisplacement();

    // Calculates the speed vector necessary to move the object to the target
    // point.
    Vector CalculateSpeed();

    // Moves the game object to the specified point.
    void Execute();

    // Stops the object.
    void PostExecute();

    // Checks whether the object is close enough to the target to consider is
    // has arrived.
    bool IsFinished();

  private:
    // Target point to move the object.
    Point target;

    // Speed at which the object will move.
    float speed;

    // Margin to consider that the object has arrived at it's target.
    float margin;
};

#endif // MOVE_ACTION_H_