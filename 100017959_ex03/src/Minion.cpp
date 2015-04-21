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

void Minion::UpdatePosition(float dt)
{
    Point minionCenter;
    Point parentCenter;

    // Keeps rotating in a circular shape around it's parent.
    circumferencePosition.Rotate(angularSpeed * dt);
    minionCenter = parent->GetCenter();
    minionCenter.Add(circumferencePosition);

    box.SetCenter(minionCenter, sprite->GetWidth(), sprite->GetHeight());
}

void Minion::UpdateBullets(float dt)
{
    for (unsigned int i = 0; i < bulletArray.size(); ++i)
        bulletArray[i]->Update(dt);
}

void Minion::DestroyBullets()
{
    for (unsigned int i = 0; i < bulletArray.size(); ++i)
    {
        if (bulletArray[i]->IsDead())
        {
            bulletArray.erase(bulletArray.begin() + i);
            --i;
        }
    }

}

void Minion::Update(float dt)
{
    DestroyBullets();
    UpdatePosition(dt);
    UpdateBullets(dt);
}

void Minion::RenderBullets()
{
    for (unsigned int i = 0; i < bulletArray.size(); ++i)
        bulletArray[i]->Render();
}

void Minion::Render()
{
    Point renderPoint;
    renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint);

    RenderBullets();
}

bool Minion::IsDead()
{
    // Minion never dies. Only it's parent can destroy it.
    return false;
}

void Minion::Shoot(Point position)
{
    Point minionPosition;
    Vector shootVector;

    minionPosition = GetCenter();
    shootVector.Set(position);
    shootVector.Subtract(minionPosition);

    bulletArray.emplace_back(new Bullet(minionPosition,
                                        shootVector.GetDirection()));
}