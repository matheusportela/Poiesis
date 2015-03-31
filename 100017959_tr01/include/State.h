// @file   State.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class definition
//
// Definition of class for a game-specific logic.

#ifndef STATE_H_
#define STATE_H_

#include <SDL.h>

#include "Sprite.h"
#include "Config.h"
#include "FileUtils.h"

// Forward declaration to avoid circular include.
class Sprite;

// This class provides game-specific logic methods.
class State
{
  public:
    // Initializes the game state.
    State();

    // Destroys the game state.
    ~State();

    // Update game state.
    void Update();

    // Render game.
    void Render();

    // Returns true if quit was requested by the user.
    bool IsQuitRequested();

    // Verifies if quit was requested by the user.
    void CheckQuitRequested();

  private:
    // Background sprite.
    Sprite* bg;

    // User requested quit flag.
    bool quitRequested;
};

#endif // STATE_H_