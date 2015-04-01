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
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "State.h"

// Forward declaration to avoid circular include.
class State;

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
    // Game singletion instance.
    static Game* instance;

    // Game window.
    SDL_Window* window;

    // Game renderer.
    SDL_Renderer* renderer;

    // Game-specific logic.
    State* state;
};

#endif // GAME_H_