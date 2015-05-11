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
    ConfigureInputCallbacks();
}

State::~State()
{
    delete tileMap;
    delete tileSet;
    delete bg;
    objectArray.clear();
}

void State::ConfigureInputCallbacks()
{
    REGISTER_INPUT_TYPE_CALLBACK(State::QuitCallback, InputType::QuitButtonPress);
    REGISTER_INPUT_KEY_CALLBACK(State::QuitCallback, InputType::KeyPress, KeyboardButton::Esc);
    REGISTER_INPUT_KEY_CALLBACK(State::AddObjectCallback, InputType::KeyPress, KeyboardButton::Space);
    REGISTER_INPUT_KEY_CALLBACK(State::DamageCallback, InputType::MousePress, MouseButton::Left);
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
    // RenderTiles();
    // RenderObjects();

    // Objects are over the first layer of the map, in order to apply properly
    // parallax effect.
    Point tile_map_point(-Camera::position.GetX(), -Camera::position.GetY());
    tileMap->RenderLayer(0, tile_map_point);
    RenderObjects();
    tileMap->RenderLayer(1, tile_map_point);
}

void State::RenderBackground()
{
    Point bg_point(0, 0);
    bg->Render(bg_point);
}

void State::RenderTiles()
{
    // Since the first upper left corner is the system origin, we use the
    // negative of the camera position to translate the origin by the amount we
    // expect to move in the screen.
    Point tile_map_point(-Camera::position.GetX(), -Camera::position.GetY());
    tileMap->Render(tile_map_point);
}

void State::RenderObjects()
{
    for (unsigned int i = 0; i < objectArray.size(); ++i)
        objectArray[i].get()->Render();
}

bool State::IsQuitRequested()
{
    return quitRequested;
}

void State::DamageCallback()
{
    Point clickPoint;
    Face* face;
    int damage;

    // Goes in backward direction to try and hit the upper objects first.
    for (int i = objectArray.size() - 1; i >= 0; --i)
    {
        // Cast pointer to Face instance, since it's the only type of GameObject
        // we have.
        // This code is temporary and will be removed soon.
        face = (Face*)objectArray[i].get();
        clickPoint = Camera::ScreenToWorldPoint(
            InputManager::GetInstance().GetMousePosition());

        // Apply damage only once
        if (face->GetBox().IsInside(clickPoint))
        {
            damage = rand() % CFG_GETI("DAMAGE_RANGE") + CFG_GETI("DAMAGE_BASE");
            face->Damage(damage);
            break;
        }
    }
}

void State::QuitCallback()
{
    quitRequested = true;
}

void State::AddObjectCallback()
{
    Point objectPoint;
    objectPoint = Camera::ScreenToWorldPoint(
        (InputManager::GetInstance().GetMousePosition()));
    AddObject(objectPoint);
}

void State::AddObject(Point& point)
{
    // Add object to a random position inside a 200-pixels radius circumference
    // relative to the given point
    float angle_deg = (float)(rand() % 360);
    float angle_rad = angle_deg*M_PI/180.0;
    Point randomPoint;
    randomPoint.SetPolar(CFG_GETF("RANDOM_RADIUS"), angle_rad);
    randomPoint.Add(point);

    objectArray.emplace_back(new Face(randomPoint));
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