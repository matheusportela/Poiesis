// @file   Game.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game engine class definition
//
// Definition of basic and generic methods for a game engine class.

#ifndef GAME_H_
#define GAME_H_

#include <ctime>
#include <cstdlib>

#include <SDL.h>
#include <SDL_image.h>

#include "ConfigParser.h"
#include "Logger.h"
#include "Resources.h"
#include "State.h"

// This class provides reusable generic methods for game development, without
// any game-specific details.
//
// Implements a singleton-like pattern.
class Game
{
  public:
    // Initializes the game engine with window title and size.
    Game(std::string title, int width, int height);

    // Destroys the game engine.
    ~Game();

    // Gets game instance as in the singleton pattern.
    static Game* GetInstance();

    // Gets the game renderer. 
    SDL_Renderer* GetRenderer();

    // Gets the game-specific logic instance.
    State& GetState();

    // Gets the amount of time passed since the last frame.
    float GetDeltaTime();

    // Seeds random number generator with current time.
    void SeedRandom();

    // Initializes game state.
    void InitState();

    // Destroys current game state.
    void DestroyState();

    // Initializes SDL engine.
    void InitSDL();

    // Initializes SDL image engine.
    void InitSDLImage();

    // Creates game window.
    void CreateWindow(std::string title, int width, int height);

    // Creates game renderer.
    void CreateRenderer();

    // Runs the game.
    void Run();

  private:
    // Updates the amount of time has passed since the last frame.
    void UpdateDeltaTime();

    // Game singletion instance.
    static Game* instance;

    // Game window.
    SDL_Window* window;

    // Game renderer.
    SDL_Renderer* renderer;

    // Game-specific logic.
    State* state;

    // Moment when the frame has started (in milliseconds).
    unsigned int frameStart;

    // Amount of time passed since the last frame (in seconds).
    float dt;
};

#endif // GAME_H_