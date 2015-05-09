// @file   ShootAction.cpp
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Shoots to a target place.

#include "ShootAction.h"

ShootAction::ShootAction(GameObject* object,
    std::vector<std::weak_ptr<GameObject>> minionArray, const Point& target) :
    Action(object), minionArray(minionArray), target(target)
{
}

int ShootAction::GetClosestMinion(const Point& point)
{
    Point minionPosition;
    int closestMinionIndex = 0;
    float closestDistance = std::numeric_limits<float>::max();
    float distance;

    for (unsigned int i = 0; i < minionArray.size(); ++i)
    {
        if (minionArray[i].expired())
            continue;

        auto minionPtr = minionArray[i].lock();
        auto minion = static_cast<Minion*>(minionPtr.get());
        minionPosition = minion->GetCenter();
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
    if (!minionArray[minionIndex].expired())
    {
        auto minionPtr = minionArray[minionIndex].lock();
        auto minion = static_cast<Minion*>(minionPtr.get());
        minion->Shoot(target);
    }
}

bool ShootAction::IsFinished()
{
    return true;
}