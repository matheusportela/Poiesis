#include "bandit/entity/EntityManager.h"

std::shared_ptr<Entity> EntityManager::CreateEntity()
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entities.push_back(entity);

    LOG_D("[EntityManager] Created entity with ID: " << entity->GetId());

    return entity;
}

void EntityManager::DeleteEntity(std::shared_ptr<Entity> entity)
{
    DeleteEntityComponents(entity);
    DeleteEntityFromContainer(entity);

    LOG_D("[EntityManager] Deleted entity with ID: " << entity->GetId());
}

void EntityManager::DeleteEntityComponents(std::shared_ptr<Entity> entity)
{
    entityToComponents.erase(entity->GetId());
}

void EntityManager::DeleteEntityFromContainer(std::shared_ptr<Entity> entity)
{
    for (unsigned int i = 0; i < entities.size(); ++i)
    {
        if (entity->GetId() == entities[i]->GetId())
        {
            entities.erase(entities.begin() + i);
            --i; // Decrease index since entities is one size smaller
        }
    }
}

void EntityManager::AddComponent(std::shared_ptr<Component> component,
    std::shared_ptr<Entity> entity)
{
    entityToComponents.insert(std::make_pair(entity->GetId(), component));

    LOG_D("[EntityManager] Added component \"" << component->GetComponentClass()
        << "\" to entity with ID: " << entity->GetId());
}

bool EntityManager::HasEntity(std::shared_ptr<Entity> entity)
{
    return (entityToComponents.find(entity->GetId()) != entityToComponents.end());
}

std::vector<std::shared_ptr<Component>> EntityManager::GetComponentsOfClass(
    std::shared_ptr<Entity> entity, std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray;

    std::shared_ptr<Component> component;
    std::pair<std::multimap<unsigned int, std::shared_ptr<Component>>::iterator,
        std::multimap<unsigned int, std::shared_ptr<Component>>::iterator> ret =
        entityToComponents.equal_range(entity->GetId());
    for (auto it = ret.first; it != ret.second; ++it)
    {
        component = it->second;
        if (component->GetComponentClass() == componentClass)
            componentsArray.push_back(component);
    }

    return componentsArray;
}

std::vector<std::shared_ptr<Entity>> EntityManager::GetAllEntitiesWithComponentOfClass(
    std::string componentClass)
{
    std::vector<std::shared_ptr<Entity>> entitiesArray;

    for (auto entity : entities)
    {
        std::shared_ptr<Component> component;
        std::pair<std::multimap<unsigned int, std::shared_ptr<Component>>::iterator,
            std::multimap<unsigned int, std::shared_ptr<Component>>::iterator> ret =
            entityToComponents.equal_range(entity->GetId());
        for (auto it = ret.first; it != ret.second; ++it)
        {
            component = it->second;
            if (component->GetComponentClass() == componentClass)
            {
                entitiesArray.push_back(entity);
                break;
            }
        }
    }

    return entitiesArray;
}

std::shared_ptr<Component> EntityManager::GetSingleComponentOfClass(
    std::shared_ptr<Entity> entity, std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray =
        GetComponentsOfClass(entity, componentClass);

    if (componentsArray.size() == 0)
    {
        LOG_E("[EntityManager] There is no component of class \""
            << componentClass << "\" in entity " << entity->GetId());
        exit(1);
    }

    if (componentsArray.size() > 1)
    {
        LOG_W("[EntityManager] Entity " << entity->GetId() << " has more than "
            << "one component of class \"" << componentClass << "\" (number of "
            << "components: " << componentsArray.size() << "). "
            << "Returning the first one.");
    }

    return componentsArray[0];
}

std::vector<std::shared_ptr<Component>> EntityManager::GetAllComponentsOfClass(
        std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray;

    for (auto entity : entities)
    {
        std::shared_ptr<Component> component;
        std::pair<std::multimap<unsigned int, std::shared_ptr<Component>>::iterator,
            std::multimap<unsigned int, std::shared_ptr<Component>>::iterator> ret =
            entityToComponents.equal_range(entity->GetId());
        for (auto it = ret.first; it != ret.second; ++it)
        {
            component = it->second;
            if (component->GetComponentClass() == componentClass)
                componentsArray.push_back(component);
        }
    }

    return componentsArray;
}

bool EntityManager::HasComponent(std::shared_ptr<Entity> entity,
        std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray =
        GetComponentsOfClass(entity, componentClass);

    return (componentsArray.size() > 0);
}

unsigned int EntityManager::GetNumberOfEntities()
{
    return entities.size();
}