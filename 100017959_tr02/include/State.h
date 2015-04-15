// @file   State.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class definition
//
// Definition of class for a game-specific logic.

#ifndef STATE_H_
#define STATE_H_

#include <cstdlib>
#include <memory>
#include <vector>

#include <SDL.h>

#include "Camera.h"
#include "ConfigParser.h"
#include "Face.h"
#include "FileUtils.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vector.h"

class TileMap;
class TileSet;

// This class provides game-specific logic methods.
class State
{
  public:
    // Initializes the game state.
    State();

    // Destroys the game state.
    ~State();

    // Configures callback functions for all relevant user input type in the game.
    void ConfigureInputCallbacks();

    // Updates game state after a delta time in seconds.
    void Update(float dt);

    // Delete game objects that are marked as IsDead.
    void DeleteDeadObjects();

    // Renders game.
    void Render();

    // Renders state background sprite.
    void RenderBackground();

    // Renders all tiles.
    void RenderTiles();

    // Renders all objects sprites.
    void RenderObjects();

    // Returns true if quit was requested by the user.
    bool IsQuitRequested();

    // Callback function for mouse input.
    void DamageCallback();

    // Callback function for quit button input.
    void QuitCallback();

    // Callback function for keyboard input.
    void AddObjectCallback();

    // Adds an object at the given point.
    void AddObject(Point& point);

  private:
    // Background sprite.
    Sprite* bg;

    // User requested quit flag.
    bool quitRequested;

    // Container for all Game Objects instanciated during the game.
    std::vector<std::unique_ptr<GameObject>> objectArray;

    // Tile management and renderization.
    TileSet* tileSet;
    TileMap* tileMap;
};

#endif // STATE_H_