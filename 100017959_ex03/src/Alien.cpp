// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#include "Alien.h"

Alien::Alien(Point point, int numMinions)
{
    hp = CFG_GETI("ALIEN_HP");
    sprite = new Sprite(CFG_GETP("ALIEN_SPRITE"));
    box.SetCenter(point, sprite->GetWidth(), sprite->GetHeight());
    angularSpeed = CFG_GETF("ALIEN_ANGULAR_SPEED");
    InitializeMinions(CFG_GETI("ALIEN_NUM_MINIONS"));

    // Rotation vector is an unitary vector, since we only need it's direction
    rotationVector.Set(1, 0);

    REGISTER_INPUT_KEY_CALLBACK(Alien::ShootCallback, InputType::MousePress,
        MouseButton::Right);
    REGISTER_INPUT_KEY_CALLBACK(Alien::MoveCallback, InputType::MousePress,
        MouseButton::Left);
}

Alien::~Alien()
{
    delete sprite;
    minionArray.clear();
}

void Alien::InitializeMinions(int numMinions)
{
    float arcOffset = 2*M_PI/numMinions;

    for (int i = 0; i < numMinions; ++i)
        minionArray.emplace_back(new Minion(this, i*arcOffset));
}

void Alien::UpdateRotation(float dt)
{
    rotationVector.Rotate(angularSpeed * dt);
    rotation = rotationVector.GetDirection();
}

void Alien::UpdatePosition(float dt)
{
    Vector displacement = speed;
    displacement.Multiply(dt);
    
    Point position = GetCenter();
    position.Add(displacement);
    box.SetCenter(position, sprite->GetWidth(), sprite->GetHeight());
}

void Alien::UpdateMinions(float dt)
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->Update(dt);
}

void Alien::Update(float dt)
{
    UpdateRotation(dt);
    UpdateMinions(dt);
}

void Alien::RenderMinions()
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->Render();
}

void Alien::Render()
{
    Point renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint, rotation);

    RenderMinions();
}

bool Alien::IsDead()
{
    return (hp <= 0);
}

int Alien::GetClosestMinion(Point point)
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

void Alien::MoveCallback()
{

}

void Alien::ShootCallback()
{
    Point point = Camera::ScreenToWorldPoint(
        InputManager::GetInstance().GetMousePosition());
    int minionIndex = GetClosestMinion(point);
    minionArray[minionIndex]->Shoot(point);
}