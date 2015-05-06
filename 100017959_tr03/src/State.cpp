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

    ConfigureInputCallbacks();
}

void State::InitializePenguins()
{
    Point position(CFG_GETI("PENGUINS_INITIAL_X"),
        CFG_GETI("PENGUINS_INITIAL_Y"));
    GameObjectManager::GetInstance().Add(std::make_shared<Penguins>(position));
}

void State::InitializeAlien()
{
    Point position(CFG_GETI("ALIEN_INITIAL_X"),
        CFG_GETI("ALIEN_INITIAL_Y"));
    int numMinions = CFG_GETI("ALIEN_NUM_MINIONS");
    GameObjectManager::GetInstance().Add(
        std::make_shared<Alien>(position, numMinions));
}

void State::ConfigureInputCallbacks()
{
    REGISTER_INPUT_TYPE_CALLBACK(State::QuitCallback,
        InputType::QuitButtonPress);
    REGISTER_INPUT_KEY_CALLBACK(State::QuitCallback,
        InputType::KeyPress, KeyboardButton::Esc);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraUpCallback,
        InputType::KeyDown, KeyboardButton::ArrowUp);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraDownCallback,
        InputType::KeyDown, KeyboardButton::ArrowDown);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraLeftCallback,
        InputType::KeyDown, KeyboardButton::ArrowLeft);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraRightCallback,
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

void State::QuitCallback()
{
    quitRequested = true;
}

void State::MoveCameraUpCallback()
{
    Point point(0, -CFG_GETI("CAMERA_MOVE_DISTANCE"));
    Camera::position.Add(point);
}

void State::MoveCameraDownCallback()
{
    Point point(0, CFG_GETI("CAMERA_MOVE_DISTANCE"));
    Camera::position.Add(point);
}

void State::MoveCameraLeftCallback()
{
    Point point(-CFG_GETI("CAMERA_MOVE_DISTANCE"), 0);
    Camera::position.Add(point);
}

void State::MoveCameraRightCallback()
{
    Point point(CFG_GETI("CAMERA_MOVE_DISTANCE"), 0);
    Camera::position.Add(point);
}