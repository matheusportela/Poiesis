// @file   Penguins.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Playable game object.

#include "Penguins.h"
#include "StageState.h"

Penguins::Penguins(const Point& position) : cannonRotation(0.0)
{
    SetSprite(CFG_GETP("PENGUINS_BODY_SPRITE"));
    SetCenter(position);
    hp = CFG_GETI("PENGUINS_HP");
    linearAcceleration = CFG_GETF("PENGUINS_ACCELERATION");
    angularSpeed = CFG_GETF("PENGUINS_ANGULAR_SPEED");
    maxLinearSpeed = CFG_GETF("PENGUINS_MAX_SPEED");
    cannonSprite = std::unique_ptr<Sprite>(
        new Sprite(CFG_GETP("PENGUINS_CANNON_SPRITE")));
    explosionSoundEffect = std::unique_ptr<SoundEffect>(
        new SoundEffect(CFG_GETP("EXPLOSION_SOUND_EFFECT")));
    ConfigureInputCommands();    
}

void Penguins::ConfigureInputCommands()
{
    speedUpCommand = CommandFactory::CreatePenguinsSpeedUpCommand(this);
    StageState::inputManager.RegisterCommand(speedUpCommand,
        InputType::KeyDown, KeyboardButton::LowercaseW);

    slowDownCommand = CommandFactory::CreatePenguinsSlowDownCommand(this);
    StageState::inputManager.RegisterCommand(slowDownCommand,
        InputType::KeyDown, KeyboardButton::LowercaseS);

    leftRotationCommand = CommandFactory::CreatePenguinsLeftRotationCommand(this);
    StageState::inputManager.RegisterCommand(leftRotationCommand,
        InputType::KeyDown, KeyboardButton::LowercaseA);

    rightRotationCommand = CommandFactory::CreatePenguinsRightRotationCommand(this);
    StageState::inputManager.RegisterCommand(rightRotationCommand,
        InputType::KeyDown, KeyboardButton::LowercaseD);

    shootCommand = CommandFactory::CreatePenguinsShootCommand(this);
    StageState::inputManager.RegisterCommand(shootCommand,
        InputType::MousePress, MouseButton::Left);
}

void Penguins::ApplyFriction()
{
    float friction = CFG_GETF("PENGUINS_FRICTION_FACTOR");
    float speedFactor = 1-friction;
    Vector speed = GetSpeed();
    SetSpeed(speed*speedFactor);
}

Point Penguins::CalculateLimitedPosition(const Point& position)
{
    Point limitedPosition = position;

    if (limitedPosition.GetX() < CFG_GETI("PENGUINS_MIN_X"))
        limitedPosition.SetX(CFG_GETI("PENGUINS_MIN_X"));

    if (limitedPosition.GetX() > CFG_GETI("PENGUINS_MAX_X"))
        limitedPosition.SetX(CFG_GETI("PENGUINS_MAX_X"));

    if (limitedPosition.GetY() < CFG_GETI("PENGUINS_MIN_Y"))
        limitedPosition.SetY(CFG_GETI("PENGUINS_MIN_Y"));

    if (limitedPosition.GetY() > CFG_GETI("PENGUINS_MAX_Y"))
        limitedPosition.SetY(CFG_GETI("PENGUINS_MAX_Y"));

    return limitedPosition;
}

void Penguins::UpdatePosition(float dt)
{
    Vector displacement = GetSpeed();
    displacement.Multiply(dt);

    // Apply the displacement to the penguin front.
    displacement.Rotate(GetRotation());
    
    Point position = GetCenter() + displacement;
    Point limitedPosition = CalculateLimitedPosition(position);
    SetCenter(limitedPosition);
}

void Penguins::UpdateCannonRotation()
{
    Point mousePosition = StageState::inputManager.GetMouseScreenPosition();
    Point cannonPosition = Camera::WorldToScreenPoint(GetCenter());

    Vector cannonToMouseVector;
    cannonToMouseVector.Set(mousePosition);
    cannonToMouseVector.Subtract(cannonPosition);

    cannonRotation = cannonToMouseVector.GetDirection();
}

void Penguins::Update(float dt)
{
    ApplyFriction();
    UpdatePosition(dt);
    UpdateCannonRotation();
    shootCooldownTimer.Update(dt);
}

void Penguins::RenderCannonSprite()
{
    Point renderPoint = Camera::WorldToScreenPoint(GetPoint());
    cannonSprite->Render(renderPoint, cannonRotation);
}

void Penguins::Render()
{
    RenderSprite();
    RenderCannonSprite();
}

void Penguins::CreateExplosionAnimation()
{
    std::string sprite = CFG_GETP("PENGUINS_EXPLOSION_SPRITE");
    int numFrames = CFG_GETI("PENGUINS_EXPLOSION_NUM_FRAMES");
    float frameDuration = CFG_GETF("PENGUINS_EXPLOSION_FRAME_TIME");

    GameObjectFactory::CreateStillAnimation(GetCenter(), sprite, numFrames,
        frameDuration, false);

}

void Penguins::OnDeath()
{
    CreateExplosionAnimation();
    explosionSoundEffect->Play(CFG_GETI("EXPLOSION_SOUND_EFFECT_TIMES"));
}

bool Penguins::IsDead()
{
    return (hp <= 0);
}

void Penguins::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("MinionBullet"))
        hp -= CFG_GETI("MINION_BULLET_DAMAGE");
}

bool Penguins::Is(std::string type)
{
    return (type == "Penguins");
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
    if (shootCooldownTimer.IsFinished())
    {
        Point bulletPosition = CalculateBulletPosition();
        GameObjectFactory::CreatePenguinsBullet(bulletPosition, cannonRotation);
        shootCooldownTimer.Set(CFG_GETF("PENGUINS_SHOOT_COOLDOWN"));
    }
}

void Penguins::ChangeSpeed(float acceleration)
{
    Vector newSpeed = GetSpeed();
    Vector deltaSpeed;

    deltaSpeed.Set(1, 0);
    deltaSpeed.Normalize();
    deltaSpeed.Multiply(acceleration);

    newSpeed.Add(deltaSpeed);
    newSpeed.Saturate(maxLinearSpeed);
    SetSpeed(newSpeed);
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
    float newRotation = GetRotation();
    newRotation -= angularSpeed;
    SetRotation(newRotation);
}

void Penguins::RightRotationCallback()
{
    float newRotation = GetRotation();
    newRotation += angularSpeed;
    SetRotation(newRotation);
}