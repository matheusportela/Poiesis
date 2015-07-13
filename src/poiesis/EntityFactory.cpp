#include "poiesis/EntityFactory.h"

std::shared_ptr<Entity> EntityFactory::CreateBackground()
{
    std::shared_ptr<Entity> background = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("BACKGROUND_IMAGE")),
        background);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(), background);
    return background;
}

std::shared_ptr<Entity> EntityFactory::CreateCell(Vector position)
{
    std::shared_ptr<Entity> cell = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ComplexityComponent>(CFG_GETI("CELL_MAX_COMPLEXITY")),
        cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(CFG_GETF("CELL_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING"),
            0, CFG_GETF("CELL_ANGULAR_VELOCITY")),
            cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<GrowthComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("CELL_COLLIDER_RADIUS")),
        cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<CombatComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<InfectionComponent>(NoInfection, false), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("CELL_ANIMATION"),
            Vector(0, 0), 0, 0, true,
            CFG_GETF("CELL_ANIMATION_SCALE"),
            CFG_GETI("CELL_ANIMATION_NUM_FRAMES"),
            CFG_GETF("CELL_ANIMATION_FRAME_DURATION"), true, true),
        cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ReproductionComponent>(1), cell);
    return cell;
}

std::shared_ptr<Entity> EntityFactory::CreatePlayer()
{
    std::shared_ptr<Entity> player = CreateCell(Vector(0, 0));
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
        std::make_shared<SpriteComponent>(CFG_GETP("FOOD_IMAGE"), Vector(0, 0),
            0, 0, true, CFG_GETF("FOOD_SCALE")), food);
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
    Random r;
    std::shared_ptr<Entity> virus = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("VIRUS_IMAGE"),
            Vector(0, 0), r.GenerateFloat(-M_PI, M_PI),
            CFG_GETF("VIRUS_ANGULAR_VELOCITY"), true,
            CFG_GETF("VIRUS_SCALE")), virus);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), virus);
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
        std::make_shared<SpriteComponent>(CFG_GETP("SLOW_AREA_ANIMATION"),
            Vector(0, 0), 0, 0, true,
            CFG_GETF("SLOW_AREA_ANIMATION_SCALE"),
            CFG_GETI("SLOW_AREA_ANIMATION_NUM_FRAMES"),
            CFG_GETF("SLOW_AREA_ANIMATION_FRAME_DURATION"), true, true),
        area);
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
        std::make_shared<SpriteComponent>(CFG_GETP("FAST_AREA_ANIMATION"),
            Vector(0, 0), 0, 0, true,
            CFG_GETF("FAST_AREA_ANIMATION_SCALE"),
            CFG_GETI("FAST_AREA_ANIMATION_NUM_FRAMES"),
            CFG_GETF("FAST_AREA_ANIMATION_FRAME_DURATION"), true, true),
        area);
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
        std::make_shared<SpriteComponent>(CFG_GETP("VITAMIN_AREA_ANIMATION"),
            Vector(0, 0), 0, 0, true,
            CFG_GETF("VITAMIN_AREA_ANIMATION_SCALE"),
            CFG_GETI("VITAMIN_AREA_ANIMATION_NUM_FRAMES"),
            CFG_GETF("VITAMIN_AREA_ANIMATION_FRAME_DURATION"), true, true),
        area);
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
        std::make_shared<SpriteComponent>(CFG_GETP("ACID_AREA_ANIMATION"),
            Vector(0, 0), 0, 0, true,
            CFG_GETF("ACID_AREA_ANIMATION_SCALE"),
            CFG_GETI("ACID_AREA_ANIMATION_NUM_FRAMES"),
            CFG_GETF("ACID_AREA_ANIMATION_FRAME_DURATION"), true, true),
        area);
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

std::shared_ptr<Entity> EntityFactory::CreateBacterium(Vector position)
{
    Random r;
    std::shared_ptr<Entity> bacterium = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), bacterium);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(CFG_GETF("BACTERIUM_INVERSE_MASS"),
            position, Vector(0, 0), Vector(0, 0), CFG_GETF("DEFAULT_DAMPING")),
        bacterium);
    Engine::GetInstance().AddComponent(
        std::make_shared<ColliderComponent>(CFG_GETF("BACTERIUM_COLLIDER_RADIUS")),
        bacterium);

    switch (r.GenerateInt(0, 3))
    {
        case 0:
            Engine::GetInstance().AddComponent(
                std::make_shared<SpriteComponent>(CFG_GETP("BACTERIUM_FROZEN_IMAGE"),
                    Vector(0, 0), r.GenerateFloat(-M_PI, M_PI), CFG_GETF("BACTERIUM_ANGULAR_VELOCITY"), true,
                    CFG_GETF("BACTERIUM_SCALE")), bacterium);
            Engine::GetInstance().AddComponent(
                std::make_shared<InfectionComponent>(CannotInput, true, false,
                    CFG_GETF("INFECTION_FROZEN_DURATION")), bacterium);
            break;
        case 1:
            Engine::GetInstance().AddComponent(
                std::make_shared<SpriteComponent>(CFG_GETP("BACTERIUM_ERRACTIC_IMAGE"),
                    Vector(0, 0), r.GenerateFloat(-M_PI, M_PI), CFG_GETF("BACTERIUM_ANGULAR_VELOCITY"), true,
                    CFG_GETF("BACTERIUM_SCALE")), bacterium);
            Engine::GetInstance().AddComponent(
                std::make_shared<InfectionComponent>(StrongImpulses, true, false,
                    CFG_GETF("INFECTION_IMPULSES_DURATION")), bacterium);
            break;
        case 2:
            Engine::GetInstance().AddComponent(
                std::make_shared<SpriteComponent>(CFG_GETP("BACTERIUM_CANNOT_EAT_IMAGE"),
                    Vector(0, 0), r.GenerateFloat(-M_PI, M_PI), CFG_GETF("BACTERIUM_ANGULAR_VELOCITY"), true,
                    CFG_GETF("BACTERIUM_SCALE")), bacterium);
            Engine::GetInstance().AddComponent(
                std::make_shared<InfectionComponent>(CannotEat, true, false,
                    CFG_GETF("INFECTION_CANNOT_EAT_DURATION")), bacterium);
            break;
        default:
            LOG_E("[EntityFactory] Bacterium type larger than permitted.");
            exit(1);
            break;
    }
    return bacterium;
}