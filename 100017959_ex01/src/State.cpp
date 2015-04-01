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
    ConfigureInputCallbacks();
}

State::~State()
{
    if (bg)
        delete bg;
}

void State::ConfigureInputCallbacks()
{
    inputManager.RegisterCallback(
        InputType::MouseInput,
        std::bind(&State::HandleMouseInput, this));
    
    inputManager.RegisterCallback(
        InputType::QuitButtonInput,
        std::bind(&State::HandleQuitButtonInput, this));

    inputManager.RegisterCallback(
        InputType::KeyboardInput,
        std::bind(&State::HandleKeyboardInput, this));
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
    Point bgPoint(0, 0);
    bg->Render(bgPoint);
    RenderObjects();    
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

void State::HandleMouseInput()
{
    Face* face;

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
            face->Damage(rand() % 10 + 10);
            std::cout << "Damage" << std::endl;
            break;
        }
    }
}

void State::HandleQuitButtonInput()
{
    quitRequested = true;
}

void State::HandleKeyboardInput()
{
    if (inputManager.GetPressedKey() == SDLK_ESCAPE)
        quitRequested = true;
    else
        AddObject(inputManager.GetMousePosition());
}

void State::AddObject(Point& point)
{
    // TODO: Add object to a random position inside a 200-pixels radius of the
    // current mouse position
    std::unique_ptr<GameObject> ptr(new Face(point));
    objectArray.push_back(std::move(ptr));
}