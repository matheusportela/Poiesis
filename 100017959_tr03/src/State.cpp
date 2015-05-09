// @file   State.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class implementation

#include "State.h"

State::State()
{
    quitRequested = false;
    bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("STATE_BACKGROUND")));
    std::unique_ptr<TileSet> tileSet(new TileSet(CFG_GETI("TILE_WIDTH"),
        CFG_GETI("TILE_HEIGHT"), CFG_GETP("TILE_SET")));
    tileMap = std::unique_ptr<TileMap>(new TileMap(CFG_GETP("TILE_MAP"),
        std::move(tileSet)));

    InitializePenguins();
    InitializeAlien();

    ConfigureInputCommands();
}

void State::InitializePenguins()
{
    Point position(CFG_GETI("PENGUINS_INITIAL_X"),
        CFG_GETI("PENGUINS_INITIAL_Y"));
    std::shared_ptr<Penguins> penguins = std::make_shared<Penguins>(position);
    GameObjectManager::GetInstance().Add(penguins, "player");
    Camera::Follow(penguins);
}

void State::InitializeAlien()
{
    Point position(CFG_GETI("ALIEN_INITIAL_X"),
        CFG_GETI("ALIEN_INITIAL_Y"));
    int numMinions = CFG_GETI("ALIEN_NUM_MINIONS");
    GameObjectManager::GetInstance().Add(
        std::make_shared<Alien>(position, numMinions));
}

void State::ConfigureInputCommands()
{
    quitCommand = std::make_shared<QuitCommand>(this);
    InputManager::GetInstance().RegisterCommand(quitCommand,
        InputType::QuitButtonPress);
    InputManager::GetInstance().RegisterCommand(quitCommand,
        InputType::KeyPress, KeyboardButton::Esc);

    cameraUpCommand = std::make_shared<CameraUpCommand>();
    InputManager::GetInstance().RegisterCommand(cameraUpCommand,
        InputType::KeyDown, KeyboardButton::ArrowUp);

    cameraDownCommand = std::make_shared<CameraDownCommand>();
    InputManager::GetInstance().RegisterCommand(cameraDownCommand,
        InputType::KeyDown, KeyboardButton::ArrowDown);
    
    cameraLeftCommand = std::make_shared<CameraLeftCommand>();
    InputManager::GetInstance().RegisterCommand(cameraLeftCommand,
        InputType::KeyDown, KeyboardButton::ArrowLeft);

    cameraRightCommand = std::make_shared<CameraRightCommand>();
    InputManager::GetInstance().RegisterCommand(cameraRightCommand,
        InputType::KeyDown, KeyboardButton::ArrowRight);
}

void State::Update(float dt)
{
    Camera::Update(dt);
    InputManager::GetInstance().ProcessInputs();
    GameObjectManager::GetInstance().Update(dt);
    CollisionSimulator::Collide();
}

void State::Render()
{
    RenderBottomTiles();
    GameObjectManager::GetInstance().Render();
    RenderTopTiles();
}

void State::RenderBottomTiles()
{
    Point bg_point(0, 0);

    // Movement illusion requires background to move in the direction opposite
    // to the camera. Hence, we negate it's position.
    Point tile_map_point = Camera::position;
    tile_map_point.Negate();

    bg->Render(bg_point);
    tileMap->RenderBaseLayer(tile_map_point);
}

void State::RenderTopTiles()
{
    // Movement illusion requires background to move in the direction opposite
    // to the camera. Hence, we negate it's position.
    Point tile_map_point = Camera::position;
    tile_map_point.Negate();
    
    tileMap->RenderUpperLayers(tile_map_point);
}

bool State::IsQuitRequested()
{
    return quitRequested;
}

void State::SetQuitRequested()
{
    quitRequested = true;
}