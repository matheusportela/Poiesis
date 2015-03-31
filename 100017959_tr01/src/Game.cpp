// @file   Game.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game engine class implementation

#include "Game.h"

Game* Game::instance = NULL;

Game::Game(std::string title, int width, int height)
{
    // Applying singleton pattern.
    if (instance != NULL)
    {
        std::cerr << "ERROR [Game] Multiple instances initialized." << std::endl;
        exit(1);
    }
    
    instance = this;
    
    InitSDL();
    InitSDLImage();
    CreateWindow(title, width, height);
    CreateRenderer();
    InitState(); // State can only be initialized after initializing the renderer.
}

Game::~Game()
{
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

void Game::InitState()
{
    state = new State();
}

void Game::DestroyState()
{
    if (state)
        delete state;
}

void Game::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "ERROR [Game] Could not initialize SDL." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Game::InitSDLImage()
{
    // Initializes only JPG loader. Returns zero when no loader could be loaded.
    if (IMG_Init(IMG_INIT_JPG) == 0)
    {
        std::cerr << "ERROR [Game] Could not initialize SDL image." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
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
        std::cerr << "ERROR [Game] Could not create window." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
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
        std::cerr << "ERROR [Game] Could not create renderer." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Game::Run()
{
    while (!state->IsQuitRequested())
    {
        state->Update();
        state->Render();
        SDL_RenderPresent(renderer); // Force image renderizing
        SDL_Delay(33); // Arbitrary delay to avoid CPU intense usage
    }
}