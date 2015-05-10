// @file   Game.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game engine class implementation

#include "Game.h"

Game* Game::instance = NULL;

Game::Game(std::string title, int width, int height) : frameStart(0), dt(0)
{
    // Applying singleton pattern.
    if (instance != NULL)
    {
        LOG_E("[Game] Multiple instances initialized.");
        exit(1);
    }
    
    instance = this;
    
    SeedRandom();
    InitSDL();
    InitSDLImage();
    CreateWindow(title, width, height);
    CreateRenderer();
    InitState(); // State can only be initialized after initializing the renderer.
}

Game::~Game()
{
    Resources::ClearImages();
    DestroyState();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

Game* Game::GetInstance()
{
    return instance;
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

State& Game::GetState()
{
    return *state;
}

float Game::GetDeltaTime()
{
    return dt;
}

void Game::SeedRandom()
{
    srand(time(NULL));
}

void Game::InitState()
{
    state = new StageState();
}

void Game::DestroyState()
{
    delete state;
}

void Game::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        LOG_E("[Game] Could not initialize SDL. " << SDL_GetError());
        exit(1);
    }
}

void Game::InitSDLImage()
{
    // Initializes only JPG loader. Returns zero when no loader could be loaded.
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        LOG_E("[Game] Could not initialize SDL image. " << SDL_GetError());
        exit(1);
    }
}

void Game::CreateWindow(std::string title, int width, int height)
{
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, 0);

    if (!window)
    {
        LOG_E("ERROR [Game] Could not create window. " << SDL_GetError());
        exit(1);
    }
}

void Game::CreateRenderer()
{
    // The second parameter decides which rendering drivers to use. -1 makes SDL
    // select the best available driver.
    //
    // SDL_RENDERER_ACCELERATED enables OpenGL or Direct3D usage.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        LOG_E("[Game] Could not create renderer. "  << SDL_GetError());
        exit(1);
    }
}

void Game::Run()
{
    while (!state->IsQuitRequested())
    {
        UpdateDeltaTime();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer); // Force image renderizing
        SDL_Delay(CFG_GETI("GAME_DELAY")); // Arbitrary delay to avoid CPU intense usage
    }

    // Clear everything from memory.
    Resources::ClearImages();
}

void Game::UpdateDeltaTime()
{
    unsigned int ticks = SDL_GetTicks();
    unsigned int delta = ticks - frameStart;
    frameStart = ticks;
    dt = delta/1000.0; // milliseconds to seconds
}