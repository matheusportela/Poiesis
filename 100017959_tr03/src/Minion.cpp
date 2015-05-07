// @file   Minion.h
// @author Matheus Vieira Portela
// @date   17/04/2015
//
// @brief Alien's minion game object

#include "Minion.h"

Minion::Minion(GameObject* parent, float arcOffset) : parent(parent),
    dead(false)
{
    SetSprite(CFG_GETP("MINION_SPRITE"));
    SetRandomScale();
    angularSpeed = CFG_GETF("MINION_ANGULAR_SPEED");
    distance = CFG_GETI("MINION_DISTANCE");
    rotationVector.SetPolar(distance, arcOffset);
}

void Minion::SetDead()
{
    dead = true;
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

void Minion::Update(float dt)
{
    UpdatePosition(dt);
}

void Minion::Render()
{
    RenderSprite();
}

bool Minion::IsDead()
{
    // Minion never dies. Only it's parent can destroy it.
    return dead;
}

void Minion::NotifyCollision(std::shared_ptr<GameObject> other)
{
}

bool Minion::Is(std::string type)
{
    return (type == "Minion");
}

void Minion::Shoot(const Point& position)
{
    Point minionPosition = GetCenter();
    Vector shootVector;
    shootVector.Set(position);
    shootVector.Subtract(minionPosition);

    GameObjectManager::GetInstance().Add(
        std::make_shared<MinionBullet>(minionPosition, shootVector.GetDirection()));
}