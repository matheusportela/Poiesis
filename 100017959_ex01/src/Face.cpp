// @file   Face.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Enemy game object

#include "Face.h"

Face::Face(Point& point)
{
    hp = 30;
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
    sprite->Render(box.GetPoint());
}

bool Face::IsDead()
{
    return (hp <= 0);
}

void Face::Damage(int damage)
{
    hp -= damage;
    std::cout << "HP: " << hp << std::endl;
}