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
    inputManager.RegisterCallback(std::bind(&State::DamageCallback, this),
        InputType::MousePress, MouseButton::Left);
    
    inputManager.RegisterCallback(std::bind(&State::QuitCallback, this),
        InputType::QuitButtonPress);

    inputManager.RegisterCallback(std::bind(&State::QuitCallback, this),
        InputType::KeyPress, KeyboardButton::Esc);

    inputManager.RegisterCallback(std::bind(&State::AddObjectCallback, this),
        InputType::KeyPress, KeyboardButton::LowercaseA);

    inputManager.RegisterCallback(std::bind(&State::AddObjectCallback, this),
        InputType::KeyPress, KeyboardButton::LowercaseW);
}

void State::Update()
{
    inputManager.ProcessInputs();
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
    RenderTiles();
    RenderObjects();
}

void State::RenderBackground()
{
    Point bg_point(0, 0);
    bg->Render(bg_point);
}

void State::RenderTiles()
{
    Point tile_map_point(0, 0);
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
    Face* face;
    int damage;

    // Goes in backward direction to try and hit the upper objects first.
    for (int i = objectArray.size() - 1; i >= 0; --i)
    {
        // Cast pointer to Face instance, since it's the only type of GameObject
        // we have.
        // This code is temporary and will be removed soon.
        face = (Face*)objectArray[i].get();

        // Apply damage only once
        if (face->GetBox().IsInside(inputManager.GetMousePosition()))
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
    AddObject(inputManager.GetMousePosition());
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