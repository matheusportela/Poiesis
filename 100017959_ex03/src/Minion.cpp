// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#include "Minion.h"

Minion::Minion(GameObject* parent, float arcOffset) : parent(parent)
{
    sprite = new Sprite(CFG_GETP("MINION_SPRITE"));
    angularSpeed = CFG_GETF("MINION_ANGULAR_SPEED");
    distance = CFG_GETF("MINION_DISTANCE");
    circumferencePosition.SetPolar(distance, arcOffset);
}

Minion::~Minion()
{
    delete sprite;
}

void Minion::Update(float dt)
{
    Point minionCenter;
    Point parentCenter;

    // Keeps rotating in a circular shape around it's parent.
    circumferencePosition.Rotate(angularSpeed * dt);
    minionCenter = parent->GetCenter();
    minionCenter.Add(circumferencePosition);

    box.SetCenter(minionCenter, sprite->GetWidth(), sprite->GetHeight());
}

void Minion::Render()
{
    Point renderPoint;
    renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint);
}

bool Minion::IsDead()
{
    // Minion never dies. Only it's parent can destroy it.
    return false;
}

void Shoot(Point position)
{
}