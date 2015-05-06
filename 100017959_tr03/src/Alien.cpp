// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#include "Alien.h"

Alien::Alien(const Point& position, int numMinions)
{
    SetSprite(CFG_GETP("ALIEN_SPRITE"));
    SetCenter(position);
    hp = CFG_GETI("ALIEN_HP");
    angularSpeed = CFG_GETF("ALIEN_ANGULAR_SPEED");
    InitializeMinions(numMinions);

    // Rotation vector is an unitary vector, since we only need it's direction
    rotationVector.Set(1, 0);
}

Alien::~Alien()
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->SetDead();
}

void Alien::InitializeMinions(int numMinions)
{
    float arcOffset = 2*M_PI/numMinions;

    for (int i = 0; i < numMinions; ++i)
    {
        minionArray.emplace_back(new Minion(this, i*arcOffset));
        GameObjectManager::GetInstance().Add(minionArray[i]);
    }
}

void Alien::UpdateRotation(float dt)
{
    rotationVector.Rotate(angularSpeed * dt);
    SetRotation(rotationVector.GetDirection());
}

void Alien::UpdatePosition(float dt)
{
    Vector displacement = GetSpeed();
    displacement.Multiply(dt);
    
    Point position = GetCenter();
    position.Add(displacement);
    SetCenter(position);
}

void Alien::Update(float dt)
{
    actionScheduler.Execute();
    UpdatePosition(dt);
    UpdateRotation(dt);
}

void Alien::Render()
{
    RenderSprite();
}

void Alien::OnDeath()
{
    LOG_D("Alien position: " << GetCenter().ToString());

    std::unique_ptr<Sprite> animatedSprite(new AnimatedSprite(
        CFG_GETP("EXPLOSION_SPRITE"), CFG_GETI("EXPLOSION_NUM_FRAMES"),
        CFG_GETF("EXPLOSION_FRAME_TIME")));
    GameObjectManager::GetInstance().Add(std::make_shared<StillAnimation>(
        GetCenter(), std::move(animatedSprite),
        CFG_GETF("STILL_ANIMATION_TEST_TIME")));
}

bool Alien::IsDead()
{
    return (hp <= 0);
}

void Alien::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("Bullet"))
        hp -= CFG_GETI("BULLET_DAMAGE");
}

bool Alien::Is(std::string type)
{
    return (type == "Alien");
}

void Alien::MoveCallback()
{
    Point point = InputManager::GetInstance().GetMouseWorldPosition();
    actionScheduler.Schedule(std::make_shared<MoveAction>(this, point,
        CFG_GETF("ALIEN_SPEED"), CFG_GETF("ALIEN_MOVE_ERROR_MARGIN")));
}

void Alien::ShootCallback()
{
    Point point = InputManager::GetInstance().GetMouseWorldPosition();
    actionScheduler.Schedule(std::make_shared<ShootAction>(this, minionArray,
        point));
}