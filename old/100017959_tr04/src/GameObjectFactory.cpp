// @file   GameObjectFactory.cppPenguins
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Create GameObject instances.

#include "GameObjectFactory.h"

#include "Alien.h"
#include "Minion.h"
#include "MinionBullet.h"
#include "Penguins.h"
#include "PenguinsBullet.h"
#include "StillAnimation.h"

void GameObjectFactory::CreatePenguins(const Point& position, std::string tag)
{
    tag = tag == "" ? "penguins" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<Penguins>(position);
    GameObjectManager::GetInstance().Add(gameObject, tag);
}

void GameObjectFactory::CreateAlien(const Point& position, int numMinions,
    std::string tag)
{
    tag = tag == "" ? "alien" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<Alien>(position, numMinions);
    GameObjectManager::GetInstance().Add(gameObject, tag);
}

std::weak_ptr<GameObject> GameObjectFactory::CreateMinion(GameObject* parent,
    float arcOffset, std::string tag)
{
    tag = tag == "" ? "minion" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<Minion>(parent, arcOffset);
    GameObjectManager::GetInstance().Add(gameObject, tag);
    return std::weak_ptr<GameObject>(gameObject);
}

void GameObjectFactory::CreateMinionBullet(const Point& position, float angle,
    std::string tag)
{
    tag = tag == "" ? "minion_bullet" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<MinionBullet>(position, angle);
    GameObjectManager::GetInstance().Add(gameObject, tag);
}

void GameObjectFactory::CreatePenguinsBullet(const Point& position,
    float angle, std::string tag)
{
    tag = tag == "" ? "penguins_bullet" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<PenguinsBullet>(position, angle);
    GameObjectManager::GetInstance().Add(gameObject, tag);
}

void GameObjectFactory::CreateStillAnimation(const Point& position,
    std::string sprite, int numFrames, float frameDuration, bool repeat,
    std::string tag)
{
    tag = tag == "" ? "still_animation" : tag;

    std::shared_ptr<GameObject> gameObject =
        std::make_shared<StillAnimation>(position, sprite, numFrames,
            frameDuration, repeat);
    GameObjectManager::GetInstance().Add(gameObject, tag);
}