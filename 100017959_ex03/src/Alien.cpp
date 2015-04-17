// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#include "Alien.h"

Alien::Alien(Point& point, int numMinions)
{
    hp = CFG_GETI("ALIEN_HP");
    sprite = new Sprite(CFG_GETP("ALIEN_SPRITE"));
    box.SetCenter(point, sprite->GetWidth(), sprite->GetHeight());
    InitializeMinions(CFG_GETI("ALIEN_NUM_MINIONS"));
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
    {
        minionArray.emplace_back(new Minion(this, i*arcOffset));
    }
}

void Alien::Update(float dt)
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->Update(dt);
}

void Alien::RenderMinions()
{
    for (unsigned int i = 0; i < minionArray.size(); ++i)
        minionArray[i]->Render();
}

void Alien::Render()
{
    Point renderPoint;
    renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint);

    RenderMinions();
}

bool Alien::IsDead()
{
    return (hp <= 0);
}