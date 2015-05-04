// @file   Penguins.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Playable game object.

#include "Penguins.h"

Penguins::Penguins(const Point& position) : cannonRotation(0.0)
{
    hp = CFG_GETI("PENGUINS_HP");
    linearAcceleration = CFG_GETF("PENGUINS_ACCELERATION");
    angularSpeed = CFG_GETF("PENGUINS_ANGULAR_SPEED");
    maxLinearSpeed = CFG_GETF("PENGUINS_MAX_SPEED");
    bodySprite = std::unique_ptr<Sprite>(
        new Sprite(CFG_GETP("PENGUINS_BODY_SPRITE")));
    cannonSprite = std::unique_ptr<Sprite>(
        new Sprite(CFG_GETP("PENGUINS_CANNON_SPRITE")));
    box.SetCenter(position, bodySprite->GetWidth(), bodySprite->GetHeight());

    REGISTER_INPUT_KEY_CALLBACK(Penguins::SpeedUpCallback,
        InputType::KeyDown, KeyboardButton::LowercaseW);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::SlowDownCallback,
        InputType::KeyDown, KeyboardButton::LowercaseS);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::LeftRotationCallback,
        InputType::KeyDown, KeyboardButton::LowercaseA);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::RightRotationCallback,
        InputType::KeyDown, KeyboardButton::LowercaseD);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::Shoot, InputType::MousePress,
        MouseButton::Left);
}

Penguins::~Penguins()
{
    bulletArray.clear();
}

void Penguins::UpdatePosition(float dt)
{
    Vector displacement = speed;
    displacement.Multiply(dt);

    // Apply the displacement to the penguin front.
    displacement.Rotate(rotation);
    
    Point position = GetCenter();
    position.Add(displacement);
    box.SetCenter(position, bodySprite->GetWidth(), bodySprite->GetHeight());
}

void Penguins::UpdateCannonRotation()
{
    Point mousePosition = InputManager::GetInstance().GetMouseScreenPosition();
    Point cannonPosition = Camera::WorldToScreenPoint(GetCenter());

    Vector cannonToMouseVector;
    cannonToMouseVector.Set(mousePosition);
    cannonToMouseVector.Subtract(cannonPosition);

    cannonRotation = cannonToMouseVector.GetDirection();
}

void Penguins::UpdateBullets(float dt)
{
    for (unsigned int i = 0; i < bulletArray.size(); ++i)
        bulletArray[i]->Update(dt);
}

void Penguins::DestroyBullets()
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

void Penguins::Update(float dt)
{
    DestroyBullets();
    UpdatePosition(dt);
    UpdateCannonRotation();
    UpdateBullets(dt);
}

void Penguins::RenderBullets()
{
    for (unsigned int i = 0; i < bulletArray.size(); ++i)
        bulletArray[i]->Render();
}

void Penguins::Render()
{
    Point renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    bodySprite->Render(renderPoint, rotation);
    cannonSprite->Render(renderPoint, cannonRotation);

    RenderBullets();
}

bool Penguins::IsDead()
{
    return (hp <= 0);
}

Point Penguins::CalculateBulletPosition()
{
    Point cannonPosition = GetCenter();
    Point bulletPosition(cannonPosition);

    Vector offset;
    offset.Set(cannonSprite->GetWidth()/2, 0);
    offset.Rotate(cannonRotation);

    bulletPosition.Add(offset);
    return bulletPosition;
}

void Penguins::Shoot()
{
    Point bulletPosition = CalculateBulletPosition();
    bulletArray.emplace_back(new Bullet(bulletPosition, cannonRotation));
}

void Penguins::ChangeSpeed(float acceleration)
{
    Vector deltaSpeed;

    deltaSpeed.Set(1, 0);
    deltaSpeed.Normalize();
    deltaSpeed.Multiply(acceleration);

    speed.Add(deltaSpeed);
    speed.Saturate(maxLinearSpeed);
}

void Penguins::SpeedUpCallback()
{
    ChangeSpeed(linearAcceleration);
}

void Penguins::SlowDownCallback()
{
    ChangeSpeed(-linearAcceleration);
}

void Penguins::LeftRotationCallback()
{
    rotation -= angularSpeed;
}

void Penguins::RightRotationCallback()
{
    rotation += angularSpeed;
}