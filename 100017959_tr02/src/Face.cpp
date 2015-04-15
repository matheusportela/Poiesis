// @file   Face.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Enemy game object

#include "Face.h"

Face::Face(Point& point)
{
    hp = CFG_GETI("FACE_HP");
    sprite = new Sprite(CFG_GETP("FACE_SPRITE"));
    box.SetCenter(point, sprite->GetWidth(), sprite->GetHeight());
}

Face::~Face()
{
    delete sprite;
}

void Face::Update(float dt)
{
}

void Face::Render()
{
    // Face object is static in the world. This means that we must render it
    // to the world point where is was spawned, not the window position. Hence,
    // we subtract the current camera position to convert to world point.
    Point renderPoint(box.GetPoint());
    renderPoint.Subtract(Camera::position);

    sprite->Render(renderPoint);
}

bool Face::IsDead()
{
    return (hp <= 0);
}

void Face::Damage(int damage)
{
    hp -= damage;
}