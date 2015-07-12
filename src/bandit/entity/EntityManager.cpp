#include "bandit/entity/EntityManager.h"

std::shared_ptr<Entity> EntityManager::CreateEntity()
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entities.push_back(entity);

    LOG_D("[EntityManager] Created entity with ID: " << entity->GetId());

    return entity;
}

void EntityManager::Clear()
{
    entities.clear();
    componentsByEntity.clear();
    componentToEntities.clear();
}

void EntityManager::DeleteEntity(std::shared_ptr<Entity> entity)
{
    DeleteEntityComponents(entity);
    DeleteEntityFromContainer(entity);

    LOG_D("[EntityManager] Deleted entity with ID: " << entity->GetId());
}

void EntityManager::DeleteEntityComponents(std::shared_ptr<Entity> entity)
{
    componentsByEntity[entity->GetId()].clear();
    componentsByEntity.erase(entity->GetId());
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

void EntityManager::DeleteEntitiesWithComponentsOfClass(
    std::string componentClass)
{
    for (unsigned int i = 0; i < entities.size(); ++i)
    {
        if (HasComponent(entities[i], componentClass))
        {
            DeleteEntity(entities[i]);
            --i; // Decrease index since entities is one size smaller
        }
    }
}

void EntityManager::AddComponent(std::shared_ptr<Component> component,
    std::shared_ptr<Entity> entity)
{
    if (HasEntity(entity))
    {
        componentsByEntity[entity->GetId()].push_back(component);
    }
    else
    {
        std::vector<std::shared_ptr<Component>> componentsArray = { component };
        componentsByEntity[entity->GetId()] = componentsArray;
    }

    LOG_D("[EntityManager] Added component \"" << component->GetComponentClass()
        << "\" to entity with ID: " << entity->GetId());
}

bool EntityManager::HasEntity(std::shared_ptr<Entity> entity)
{
    return (componentsByEntity.find(entity->GetId()) != componentsByEntity.end());
}

std::vector<std::shared_ptr<Component>> EntityManager::GetComponentsOfClass(
    std::shared_ptr<Entity> entity, std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray;

    for (auto component : componentsByEntity[entity->GetId()])
    {
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
        for (auto component : componentsByEntity[entity->GetId()])
        {
            if (component->GetComponentClass() == componentClass)
            {
                entitiesArray.push_back(entity);
                break;
            }
        }
    }

    return entitiesArray;
}

std::shared_ptr<Entity> EntityManager::GetEntityWithComponentOfClass(
        std::string componentClass)
{
    std::vector<std::shared_ptr<Entity>> entitiesArray =
        GetAllEntitiesWithComponentOfClass(componentClass);

    if (entitiesArray.size() == 0)
    {
        LOG_E("[EntityManager] There is no entity with component of class \""
            << componentClass << "\"");
        exit(1);
    }

    if (entitiesArray.size() > 1)
    {
        LOG_W("[EntityManager] More than one entity contains a component of "
            << "class \"" << componentClass << "\" (number of entities: "
            << entitiesArray.size() << "). Returning the first one.");
    }

    return entitiesArray[0];
}

bool EntityManager::HasEntityWithComponentOfClass(std::string componentClass)
{
    return (GetAllEntitiesWithComponentOfClass(componentClass).size() > 0);
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
        for (auto component : componentsByEntity[entity->GetId()])
        {
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

void EntityManager::DeleteComponentsOfClass(std::shared_ptr<Entity> entity,
    std::string componentClass)
{
    std::shared_ptr<Component> component;

    for (unsigned int i = 0; i < componentsByEntity[entity->GetId()].size(); ++i)
    {
        component = componentsByEntity[entity->GetId()][i];

        if (component->GetComponentClass() == componentClass)
        {
            componentsByEntity[entity->GetId()].erase(componentsByEntity[entity->GetId()].begin() + i);
            --i; // Decrease index since entities is one size smaller
        }
    }
}