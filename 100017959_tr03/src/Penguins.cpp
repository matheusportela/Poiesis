// @file   Penguins.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Playable game object.

#include "Penguins.h"

Penguins::Penguins(Point position)
{
    bodySprite = new Sprite(CFG_GETP("PENGUINS_BODY_SPRITE"));
    cannonSprite = new Sprite(CFG_GETP("PENGUINS_CANNON_SPRITE"));
    box.SetCenter(position, bodySprite->GetWidth(), bodySprite->GetHeight());
}

Penguins::~Penguins()
{
    delete cannonSprite;
    delete bodySprite;
}


void Penguins::Update(float dt)
{

}

void Penguins::Render()
{
    Point renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    bodySprite->Render(renderPoint);
    cannonSprite->Render(renderPoint);
}

bool Penguins::IsDead()
{
    return (hp <= 0);
}

void Penguins::Shoot()
{

}