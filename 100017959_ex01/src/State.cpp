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
}

State::~State()
{
    delete bg;
    objectArray.clear();
}

void State::Update()
{
    Input();
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
    RenderObjects();    
}

void State::RenderBackground()
{
    Point bgPoint(0, 0);
    bg->Render(bgPoint);
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

void State::Input()
{
    SDL_Event event;
    int mouse_x, mouse_y;
    Point mouse_point;

    // Store mouse coordinates
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_point.Set(mouse_x, mouse_y);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quitRequested = true;
       
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Iterate from the last created object to the first one
            for (int i = objectArray.size() - 1; i >= 0; --i)
            {
                // This hardcoded cast is temporary and will be removed soon
                Face* face = (Face*) objectArray[i].get();

                if (face->GetBox().IsInside(mouse_point))
                {
                    face->Damage(rand() % 10 + 10);

                    // Apply damage only once
                    break;
                }
            }
        }
        
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                quitRequested = true;
            else
                AddObject(mouse_point);
        }
    }
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