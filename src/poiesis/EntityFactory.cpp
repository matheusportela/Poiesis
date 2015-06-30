#include "poiesis/EntityFactory.h"

std::shared_ptr<Entity> EntityFactory::CreateBackground()
{
    std::shared_ptr<Entity> background = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("BACKGROUND_IMAGE"),
            Vector(0, 0), true),
        background);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(), background);
    return background;
}

std::shared_ptr<Entity> EntityFactory::CreateCell(std::string image,
    Vector position)
{
    std::shared_ptr<Entity> cell = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(image), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(CFG_GETF("CELL_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
            cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<GrowthComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("CELL_COLLIDER_RADIUS")),
        cell);
    Engine::GetInstance().AddComponent(std::make_shared<AIComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<CombatComponent>(), cell);
    return cell;
}

std::shared_ptr<Entity> EntityFactory::CreateCell(int type,
    Vector position)
{
    std::shared_ptr<Entity> cell;

    switch (type)
    {
        case 1:
            // return CreateCell(CFG_GETP("CELL_1_IMAGE"), position);
            cell = Engine::GetInstance().CreateEntity();
            Engine::GetInstance().AddComponent(
                std::make_shared<SpriteComponent>(CFG_GETP("CELL_1_ANIMATION"), Vector(0, 0), true, 1, CFG_GETI("CELL_1_ANIMATION_NUM_FRAMES"), CFG_GETI("CELL_1_ANIMATION_FRAME_DURATION"), true), cell);
            Engine::GetInstance().AddComponent(
                std::make_shared<MoveableComponent>(), cell);
            Engine::GetInstance().AddComponent(
                std::make_shared<ParticleComponent>(CFG_GETF("CELL_INVERSE_MASS"),
                    position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
                    cell);
            Engine::GetInstance().AddComponent(
                std::make_shared<GrowthComponent>(), cell);
            Engine::GetInstance().AddComponent(
                std::make_shared<ColliderComponent>(CFG_GETF("CELL_COLLIDER_RADIUS")),
                cell);
            Engine::GetInstance().AddComponent(std::make_shared<AIComponent>(), cell);
            Engine::GetInstance().AddComponent(
                std::make_shared<CombatComponent>(), cell);
            return cell;
        case 2:
            return CreateCell(CFG_GETP("CELL_2_IMAGE"), position);
        case 3:
            return CreateCell(CFG_GETP("CELL_3_IMAGE"), position);
        case 4:
            return CreateCell(CFG_GETP("CELL_4_IMAGE"), position);
        case 5:
            return CreateCell(CFG_GETP("CELL_5_IMAGE"), position);
        default:
            LOG_E("[EntityFactory] Unknown cell type: " << type);
            exit(1);
    }
}

std::shared_ptr<Entity> EntityFactory::CreatePlayer()
{
    std::shared_ptr<Entity> player = CreateCell(1, Vector(0, 0));
    Engine::GetInstance().AddComponent(
        std::make_shared<PlayerComponent>(), player);
    Engine::GetInstance().AddComponent(
        std::make_shared<CameraFollowComponent>(), player);
    return player;
}

std::shared_ptr<Entity> EntityFactory::CreateFood(Vector position)
{
    std::shared_ptr<Entity> food = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("FOOD_IMAGE")), food);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), food);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(CFG_GETF("FOOD_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
        food);
    Engine::GetInstance().AddComponent(
        std::make_shared<EatableComponent>(), food);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("FOOD_COLLIDER_RADIUS")),
        food);
    return food;
}

std::shared_ptr<Entity> EntityFactory::CreateCamera()
{
    std::shared_ptr<Entity> camera = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<CameraComponent>(), camera);
    return camera;
}

std::shared_ptr<Entity> EntityFactory::CreateSlowArea(Vector position)
{
    std::shared_ptr<Entity> area = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("SLOW_AREA_IMAGE")), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, position), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("SLOW_AREA_COLLIDER_RADIUS")),
        area);
    Engine::GetInstance().AddComponent(
        std::make_shared<SlowingComponent>(CFG_GETF("SLOW_AREA_MAGNITUDE")), area);
    return area;
}

std::shared_ptr<Entity> EntityFactory::CreateFastArea(Vector position)
{
    std::shared_ptr<Entity> area = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("FAST_AREA_IMAGE")), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, position), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("FAST_AREA_COLLIDER_RADIUS")),
        area);
    Engine::GetInstance().AddComponent(
        std::make_shared<SlowingComponent>(CFG_GETF("FAST_AREA_MAGNITUDE")), area);
    return area;
}

std::shared_ptr<Entity> EntityFactory::CreateButton(std::string image,
    Rectangle rectangle, std::function<void()> callback)
{
    std::shared_ptr<Entity> button = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(image), button);
    Engine::GetInstance().AddComponent(
        std::make_shared<ButtonComponent>(rectangle, callback), button);
    return button;
}

