// @file   GameObjectFactory.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Create GameObject instances.
//
// Each created object is owned by GameObjectManager, hence, the create method
// places the new object in the manager.

#ifndef GAME_OBJECT_FACTORY_H_
#define GAME_OBJECT_FACTORY_H_

#include <memory>
#include <string>

#include "GameObject.h"
#include "GameObjectManager.h"

class GameObjectFactory
{
  public:
    static void CreatePenguins(const Point& position,
        std::string tag = "");
    static void CreateAlien(const Point& position,
        int numMinions, std::string tag = "");
    static std::weak_ptr<GameObject> CreateMinion(GameObject* parent,
        float arcOffset, std::string tag = "");
    static void CreateMinionBullet(const Point& position,
        float angle, std::string tag = "");
    static void CreatePenguinsBullet(const Point& position,
        float angle, std::string tag = "");
    static void CreateStillAnimation(const Point& position, std::string sprite,
        int numFrames, float frameDuration, bool repeat, std::string tag = "");
};

#endif // GAME_OBJECT_FACTORY_H_