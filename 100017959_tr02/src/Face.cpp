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
    Point renderPoint;
    renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
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