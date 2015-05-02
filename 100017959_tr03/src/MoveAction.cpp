// @file   MoveAction.cpp
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Moves a game object to a target point.

#include "MoveAction.h"

MoveAction::MoveAction(GameObject* object, Point target, float speed,
    float margin) : Action(object), target(target), speed(speed), margin(margin)
{
}

Vector MoveAction::CalculateDisplacement()
{
    Vector displacement;
    displacement.Set(target);
    displacement.Subtract(attachedObject->GetCenter());
    return displacement;
}

Vector MoveAction::CalculateSpeed()
{
    Vector speedVector;
    Vector displacement = CalculateDisplacement();
    speedVector.Set(displacement);
    speedVector.Normalize();
    speedVector.Multiply(speed);
    return speedVector;
}

void MoveAction::Execute()
{
    Vector speedVector = CalculateSpeed();
    attachedObject->SetSpeed(speedVector);
}

void MoveAction::PostExecute()
{
    Vector speedVector;
    speedVector.Set(0, 0);
    attachedObject->SetSpeed(speedVector);
}

bool MoveAction::IsFinished()
{
    Vector displacement = CalculateDisplacement();
    return (displacement.GetMagnitude() <= margin);
}