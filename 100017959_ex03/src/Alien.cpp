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

bool Alien::IsMoveFinished(Point target, float errorMargin)
{
    Vector displacement;
    displacement.Set(target);
    displacement.Subtract(GetCenter());

    return (displacement.GetMagnitude() <= errorMargin);
}

bool Alien::ExecuteMoveAction(Point target)
{
    speed.Set(target);
    speed.Subtract(GetCenter());
    speed.Normalize();
    speed.Multiply(CFG_GETI("ALIEN_SPEED"));

    return IsMoveFinished(target, CFG_GETI("ALIEN_MOVE_ERROR_MARGIN"));
}

void Alien::ExecuteAction()
{
    bool finished = false;

    if (taskQueue.size() > 0)
    {
        Alien::Action& action = taskQueue.front();

        switch (action.type)
        {
            case Alien::Action::Move:
                finished = ExecuteMoveAction(action.target);
                break;
            case Alien::Action::Shoot:
                finished = true;
                break;
        }
    }

    if (finished)
    {
        speed.Set(0, 0);
        taskQueue.pop();
    }
}

void Alien::Update(float dt)
{
    ExecuteAction();
    UpdatePosition(dt);
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

void Alien::ScheduleAction(Alien::Action action)
{
    taskQueue.push(action);
}

void Alien::ScheduleMoveAction(Point point)
{
    Alien::Action moveAction(Action::Move, point);
    ScheduleAction(moveAction);
}

void Alien::MoveCallback()
{
    Point point = InputManager::GetInstance().GetMouseWorldPosition();
    ScheduleMoveAction(point);
}

void Alien::ShootCallback()
{
    LOG_D("Alien shoot callback");

    Point point = InputManager::GetInstance().GetMouseWorldPosition();
    int minionIndex = GetClosestMinion(point);
    minionArray[minionIndex]->Shoot(point);
}