// @file   State.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class implementation

#include "State.h"

State::State()
{
    quitRequested = false;
    bg = new Sprite(CFG_GETP("STATE_BACKGROUND"));
    tileSet = new TileSet(CFG_GETI("TILE_WIDTH"), CFG_GETI("TILE_HEIGHT"),
        CFG_GETP("TILE_SET"));
    tileMap = new TileMap(CFG_GETP("TILE_MAP"), tileSet);

    InitializePenguins();
    InitializeAlien();

    ConfigureInputCallbacks();
}

State::~State()
{
    delete tileMap;
    delete tileSet;
    delete bg;
    objectArray.clear();
}

void State::InitializePenguins()
{
    Point penguinsPosition(CFG_GETI("PENGUINS_INITIAL_X"),
        CFG_GETI("PENGUINS_INITIAL_Y"));
    objectArray.emplace_back(new Penguins(penguinsPosition));
}

void State::InitializeAlien()
{
    Point alienPosition(CFG_GETI("ALIEN_INITIAL_X"),
        CFG_GETI("ALIEN_INITIAL_Y"));
    objectArray.emplace_back(new Alien(alienPosition, 1));
}

void State::ConfigureInputCallbacks()
{
    REGISTER_INPUT_TYPE_CALLBACK(State::QuitCallback, InputType::QuitButtonPress);
    REGISTER_INPUT_KEY_CALLBACK(State::QuitCallback, InputType::KeyPress, KeyboardButton::Esc);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraUpCallback, InputType::KeyDown, KeyboardButton::ArrowUp);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraDownCallback, InputType::KeyDown, KeyboardButton::ArrowDown);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraLeftCallback, InputType::KeyDown, KeyboardButton::ArrowLeft);
    REGISTER_INPUT_KEY_CALLBACK(State::MoveCameraRightCallback, InputType::KeyDown, KeyboardButton::ArrowRight);
}

void State::Update(float dt)
{
    Camera::Update(dt);
    InputManager::GetInstance().ProcessInputs();
    DeleteDeadObjects();

    for (unsigned int i = 0; i < objectArray.size(); ++i)
        objectArray[i]->Update(dt);
}

void State::DeleteDeadObjects()
{
    for (unsigned int i = 0; i < objectArray.size(); ++i)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);

            // Decrease index since objectArray is one size smaller
            --i;
        }
    }
}

void State::Render()
{
    RenderBackground();
    RenderObjects();
    RenderUpperObjects();
}

void State::RenderBackground()
{
    Point bg_point(0, 0);

    // Movement illusion requires background to move in the direction opposite
    // to the camera. Hence, we negate it's position.
    Point tile_map_point = Camera::position;
    tile_map_point.Negate();

    bg->Render(bg_point);
    tileMap->RenderBaseLayer(tile_map_point);
}

void State::RenderObjects()
{
    for (unsigned int i = 0; i < objectArray.size(); ++i)
        objectArray[i].get()->Render();
}

void State::RenderUpperObjects()
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