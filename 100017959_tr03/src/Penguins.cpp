// @file   Penguins.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Playable game object.

#include "Penguins.h"

Penguins::Penguins(Point position)
{
    hp = CFG_GETI("PENGUINS_HP");
    linearAcceleration = CFG_GETF("PENGUINS_ACCELERATION");
    angularSpeed = CFG_GETF("PENGUINS_ANGULAR_SPEED");
    bodySprite = new Sprite(CFG_GETP("PENGUINS_BODY_SPRITE"));
    cannonSprite = new Sprite(CFG_GETP("PENGUINS_CANNON_SPRITE"));
    box.SetCenter(position, bodySprite->GetWidth(), bodySprite->GetHeight());

    REGISTER_INPUT_KEY_CALLBACK(Penguins::SpeedUpCallback,
        InputType::KeyDown, KeyboardButton::LowercaseW);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::SlowDownCallback,
        InputType::KeyDown, KeyboardButton::LowercaseS);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::LeftRotationCallback,
        InputType::KeyDown, KeyboardButton::LowercaseA);
    REGISTER_INPUT_KEY_CALLBACK(Penguins::RightRotationCallback,
        InputType::KeyDown, KeyboardButton::LowercaseD);
}

Penguins::~Penguins()
{
    delete cannonSprite;
    delete bodySprite;
}

void Penguins::UpdatePosition(float dt)
{
    Vector displacement = speed;
    displacement.Multiply(dt);
    
    Point position = GetCenter();
    position.Add(displacement);
    box.SetCenter(position, bodySprite->GetWidth(), bodySprite->GetHeight());
}

void Penguins::Update(float dt)
{
    LOG_D("[Penguins] Speed: " << speed.ToString());
    UpdatePosition(dt);
}

void Penguins::Render()
{
    Point renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    bodySprite->Render(renderPoint, rotation);
    cannonSprite->Render(renderPoint, rotation);
}

bool Penguins::IsDead()
{
    return (hp <= 0);
}

void Penguins::Shoot()
{

}

void Penguins::ChangeSpeed(float acceleration)
{
    Vector deltaSpeed;

    deltaSpeed.Set(1, 0);
    deltaSpeed.Normalize();
    deltaSpeed.Multiply(acceleration);

    speed.Add(deltaSpeed);
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
    rotation += angularSpeed;
}

void Penguins::RightRotationCallback()
{
    rotation -= angularSpeed;
}