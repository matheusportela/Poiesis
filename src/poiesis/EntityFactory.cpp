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

std::shared_ptr<Entity> EntityFactory::CreateCellWithoutSprite(Vector position)
{
    std::shared_ptr<Entity> cell = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<CellComponent>(), cell);
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

std::shared_ptr<Entity> EntityFactory::CreateCell(std::string image,
    Vector position)
{
    std::shared_ptr<Entity> cell = CreateCellWithoutSprite(position);
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(image), cell);
    return cell;
}

std::shared_ptr<Entity> EntityFactory::CreateAnimatedCell(std::string image,
    int numFrames, float frameDuration, Vector position)
{
    std::shared_ptr<Entity> cell = CreateCellWithoutSprite(position);
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(image, Vector(0, 0), true, 1,
            numFrames, frameDuration, true), cell);
    return cell;
}

std::shared_ptr<Entity> EntityFactory::CreateCell(int type,
    Vector position)
{
    std::shared_ptr<Entity> cell;

    switch (type)
    {
        case 1:
            return CreateAnimatedCell(CFG_GETP("CELL_1_ANIMATION"),
                CFG_GETI("CELL_1_ANIMATION_NUM_FRAMES"),
                CFG_GETF("CELL_1_ANIMATION_FRAME_DURATION"), position);
        case 2:
            return CreateAnimatedCell(CFG_GETP("CELL_2_ANIMATION"),
                CFG_GETI("CELL_2_ANIMATION_NUM_FRAMES"),
                CFG_GETF("CELL_2_ANIMATION_FRAME_DURATION"), position);
        case 3:
            return CreateAnimatedCell(CFG_GETP("CELL_3_ANIMATION"),
                CFG_GETI("CELL_3_ANIMATION_NUM_FRAMES"),
                CFG_GETF("CELL_3_ANIMATION_FRAME_DURATION"), position);
        case 4:
            return CreateAnimatedCell(CFG_GETP("CELL_4_ANIMATION"),
                CFG_GETI("CELL_4_ANIMATION_NUM_FRAMES"),
                CFG_GETF("CELL_4_ANIMATION_FRAME_DURATION"), position);
        case 5:
            return CreateAnimatedCell(CFG_GETP("CELL_5_ANIMATION"),
                CFG_GETI("CELL_5_ANIMATION_NUM_FRAMES"),
                CFG_GETF("CELL_5_ANIMATION_FRAME_DURATION"), position);
        default:
            LOG_E("[EntityFactory] Unknown cell type: " << type);
            exit(1);
    }
}

std::shared_ptr<Entity> EntityFactory::CreateRandomCell(Vector position)
{
    Random r;
    int type = r.GenerateInt(1, 6);
    return CreateCell(type, position);
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

std::shared_ptr<Entity> EntityFactory::CreateCellParticle(Vector position)
{
    std::shared_ptr<Entity> cellParticle = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("CELL_PARTICLE_IMAGE")),
        cellParticle);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), cellParticle);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(
            CFG_GETF("CELL_PARTICLE_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
        cellParticle);
    Engine::GetInstance().AddComponent(
        std::make_shared<EatableComponent>(), cellParticle);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(
            CFG_GETF("CELL_PARTICLE_COLLIDER_RADIUS")),
        cellParticle);
    Engine::GetInstance().AddComponent(
        std::make_shared<CellParticleComponent>(), cellParticle);
    return cellParticle;
}

std::shared_ptr<Entity> EntityFactory::CreateVirus(Vector position)
{
    std::shared_ptr<Entity> virus = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("VIRUS_IMAGE")), virus);
    // Engine::GetInstance().AddComponent(
    //     std::make_shared<MoveableComponent>(), virus);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(CFG_GETF("VIRUS_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
        virus);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("VIRUS_COLLIDER_RADIUS")),
        virus);
    Engine::GetInstance().AddComponent(
        std::make_shared<CombatComponent>(CFG_GETI("VIRUS_COMBAT_POWER")),
        virus);
    return virus;
}

std::shared_ptr<Entity> EntityFactory::CreateCamera(float height)
{
    std::shared_ptr<Entity> camera = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<CameraComponent>(Vector(0, 0), height), camera);
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

std::shared_ptr<Entity> EntityFactory::CreateVitaminArea(Vector position)
{
    std::shared_ptr<Entity> area = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("VITAMIN_AREA_IMAGE")), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, position), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("VITAMIN_AREA_COLLIDER_RADIUS")),
        area);
    Engine::GetInstance().AddComponent(
        std::make_shared<VitaminComponent>(CFG_GETF("VITAMIN_AREA_GROWTH_FACTOR")),
        area);
    return area;
}

std::shared_ptr<Entity> EntityFactory::CreateAcidArea(Vector position)
{
    std::shared_ptr<Entity> area = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("ACID_AREA_IMAGE")), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(0, position), area);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("ACID_AREA_COLLIDER_RADIUS")),
        area);
    Engine::GetInstance().AddComponent(
        std::make_shared<VitaminComponent>(CFG_GETF("ACID_AREA_GROWTH_FACTOR")),
        area);
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

