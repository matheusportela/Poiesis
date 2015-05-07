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

    behavior = 0;

    // Rotation vector is an unitary vector, since we only need it's direction
    rotationVector.Set(1, 0);
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
    switch (behavior)
    {
        case 0:
            MoveBehavior();
            break;
        case 1:
            ShootBehavior();
            break;
        case 2:
            RestBehavior();
            break;
    }

    actionScheduler.Execute();
    shootCooldown.Update(dt);
    UpdatePosition(dt);
    UpdateRotation(dt);
}

void Alien::Render()
{
    RenderSprite();
}

void Alien::CreateExplosionAnimation()
{
    int numFrames = CFG_GETI("ALIEN_EXPLOSION_NUM_FRAMES");
    float frameDuration = CFG_GETF("ALIEN_EXPLOSION_FRAME_TIME");
    float animationDuration = numFrames*frameDuration;
    std::unique_ptr<Sprite> animatedSprite(new AnimatedSprite(
        CFG_GETP("ALIEN_EXPLOSION_SPRITE"), numFrames, frameDuration));
    GameObjectManager::GetInstance().Add(std::make_shared<StillAnimation>(
        GetCenter(), std::move(animatedSprite), animationDuration));
}

void Alien::OnDeath()
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->SetDead();

    CreateExplosionAnimation();
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

void Alien::MoveBehavior()
{
    if (actionScheduler.GetQueueSize() == 0)
    {
        LOG_D("Move behavior");

        std::shared_ptr<GameObject> playerObject =
            GameObjectManager::GetInstance().GetObject("player");
        Point point = playerObject->GetCenter();
        actionScheduler.Schedule(std::make_shared<MoveAction>(this, point,
            CFG_GETF("ALIEN_SPEED"), CFG_GETF("ALIEN_MOVE_ERROR_MARGIN")));

        behavior = 1;
    }
}

void Alien::ShootBehavior()
{
    if (actionScheduler.GetQueueSize() == 0)
    {
        LOG_D("Shoot behavior");

        std::shared_ptr<GameObject> playerObject =
            GameObjectManager::GetInstance().GetObject("player");
        Point point = playerObject->GetCenter();
        actionScheduler.Schedule(std::make_shared<ShootAction>(this, minionArray,
            point));

        shootCooldown.Set(CFG_GETF("ALIEN_REST_BEHAVIOR_TIME"));
        behavior = 2;
    }
}

void Alien::RestBehavior()
{
    if (shootCooldown.IsFinished())
    {
        LOG_D("Rest behavior");

        behavior = 0;
    }
}