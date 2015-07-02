// Manages entities creation, destruction and queries.

#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <unordered_map>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "bandit/core/Log.h"
#include "bandit/entity/Component.h"
#include "bandit/entity/Entity.h"

class EntityManager
{
  public:
    // Creates a new entity.
    std::shared_ptr<Entity> CreateEntity();

    // Clears everything from entity manager.
    void Clear();

    // Deletes an entity from the management.
    void DeleteEntity(std::shared_ptr<Entity> entity);

    // Adds a new component to an existing entity.
    void AddComponent(std::shared_ptr<Component> component,
        std::shared_ptr<Entity> entity);

    // Gets all components of the given class from an entity.
    std::vector<std::shared_ptr<Component>> GetComponentsOfClass(
        std::shared_ptr<Entity> entity, std::string componentClass);

    // Gets all entities that has a specific component class attached to it.
    std::vector<std::shared_ptr<Entity>> GetAllEntitiesWithComponentOfClass(
        std::string componentClass);

    // Gets a single component that has a specific component class attached to
    // it.
    std::shared_ptr<Entity> GetEntityWithComponentOfClass(
        std::string componentClass);

    // Gets a single component of a given class from an entity.
    std::shared_ptr<Component> GetSingleComponentOfClass(
        std::shared_ptr<Entity> entity, std::string componentClass);

    // Gets all components from all entities that matches the given class.
    std::vector<std::shared_ptr<Component>> GetAllComponentsOfClass(
        std::string componentClass);

    // Checks whether an entity has at least one component of the given class.
    bool HasComponent(std::shared_ptr<Entity> entity,
        std::string componentClass);

    // Gets the number of entities currently managed.
    unsigned int GetNumberOfEntities();

  private:
    void DeleteEntityComponents(std::shared_ptr<Entity> entity);
    void DeleteEntityFromContainer(std::shared_ptr<Entity> entity);
    bool HasEntity(std::shared_ptr<Entity> entity);

    // All entities in the game.
    std::vector<std::shared_ptr<Entity>> entities;

    // Stores all components attached to a given entity.
    std::unordered_map<unsigned int, std::vector<std::shared_ptr<Component>>>
        componentsByEntity;

    // Stores all entities that have a given component type.
    std::multimap<std::string, std::shared_ptr<Entity>> componentToEntities;
};

#endif // ENTITY_MANAGER_H_