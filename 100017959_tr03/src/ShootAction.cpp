// @file   ShootAction.cpp
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Shoots to a target place.

#include "ShootAction.h"

ShootAction::ShootAction(GameObject* object,
    std::vector<std::shared_ptr<Minion>> minionArray, Point target) :
    Action(object), minionArray(minionArray), target(target)
{
}

int ShootAction::GetClosestMinion(Point point)
{
    Point minionPosition;
    int closestMinionIndex = 0;
    float closestDistance = std::numeric_limits<float>::max();
    float distance;

    for (unsigned int i = 0; i < minionArray.size(); ++i)
    {
        minionPosition = minionArray[i]->GetCenter();
        distance = minionPosition.CalculateDistance(point);

        if (distance < closestDistance)
        {
            closestMinionIndex = i;
            closestDistance = distance;
        }
    }

    return closestMinionIndex;
}

void ShootAction::Execute()
{
    int minionIndex = GetClosestMinion(target);
    minionArray[minionIndex]->Shoot(target);
}

bool ShootAction::IsFinished()
{
    return true;
}