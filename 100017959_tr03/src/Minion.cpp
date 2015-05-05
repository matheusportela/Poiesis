// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#include "Minion.h"

Minion::Minion(GameObject* parent, float arcOffset) : parent(parent)
{
    SetSprite(CFG_GETP("MINION_SPRITE"));
    SetRandomScale();
    angularSpeed = CFG_GETF("MINION_ANGULAR_SPEED");
    distance = CFG_GETI("MINION_DISTANCE");
    rotationVector.SetPolar(distance, arcOffset);
}

Minion::~Minion()
{
    bulletArray.clear();
}

void Minion::SetRandomScale()
{
    float min_scale = CFG_GETF("MINION_MIN_SCALE");
    float max_scale = CFG_GETF("MINION_MAX_SCALE");

    // Generating a random number in the interval [min_scale, max_scale]
    float scale = min_scale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max_scale-min_scale)));
    SetScale(scale);
}

void Minion::UpdatePosition(float dt)
{
    // Keeps rotating in a circular shape around it's parent.
    rotationVector.Rotate(angularSpeed * dt);

    Point minionCenter = parent->GetCenter();
    minionCenter.Add(rotationVector);

    SetCenter(minionCenter);
    SetRotation(rotationVector.GetDirection());
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
    RenderSprite();
    RenderBullets();
}

bool Minion::IsDead()
{
    // Minion never dies. Only it's parent can destroy it.
    return false;
}

void Minion::Shoot(const Point& position)
{
    Point minionPosition = GetCenter();
    Vector shootVector;
    shootVector.Set(position);
    shootVector.Subtract(minionPosition);

    bulletArray.emplace_back(new Bullet(minionPosition,
                                        shootVector.GetDirection()));
}