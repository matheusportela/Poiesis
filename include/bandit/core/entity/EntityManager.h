// Manages entities creation, destruction and queries.

#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "bandit/core/Log.h"
#include "bandit/core/entity/Component.h"
#include "bandit/core/entity/Entity.h"

class EntityManager
{
  public:
    std::shared_ptr<Entity> CreateEntity();
    void DeleteEntity(std::shared_ptr<Entity> entity);
    void AddComponent(std::shared_ptr<Component> component,
        std::shared_ptr<Entity> entity);
    std::vector<std::shared_ptr<Component>> GetComponentsOfClass(
        std::shared_ptr<Entity> entity, std::string componentClass);
    std::vector<std::shared_ptr<Entity>> GetAllEntitiesWithComponentOfClass(
        std::string componentClass);

  // private:
    void DeleteEntityComponents(std::shared_ptr<Entity> entity);
    void DeleteEntityFromContainer(std::shared_ptr<Entity> entity);
    bool HasEntity(std::shared_ptr<Entity> entity);

    std::vector<std::shared_ptr<Entity>> entities;
    std::map<unsigned int, std::vector<std::shared_ptr<Component>>>
        componentsByEntity;
};

#endif // ENTITY_MANAGER_H_