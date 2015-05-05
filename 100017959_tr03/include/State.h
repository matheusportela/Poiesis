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

#include "Alien.h"
#include "Camera.h"
#include "ConfigParser.h"
#include "FileUtils.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Penguins.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vector.h"

// This class provides game-specific logic methods.
class State
{
  public:
    // Initializes the game state.
    State();

    // Destroys the game state.
    ~State();

    // Initialize Penguins game object.
    void InitializePenguins();

    // Initialize Alien game object.
    void InitializeAlien();

    // Configures callback functions for all relevant user input type in the game.
    void ConfigureInputCallbacks();

    // Updates game state after a delta time in seconds.
    void Update(float dt);

    // Delete game objects that are marked as IsDead.
    void DeleteDeadObjects();

    // Renders game.
    void Render();

    // Renders all sprites that stays behind the game characters.
    void RenderBackground();

    // Renders all sprites that stays in the same level as the game characters.
    void RenderObjects();

    // Renders all sprites that stays above the game characters.
    void RenderUpperObjects();

    // Returns true if quit was requested by the user.
    bool IsQuitRequested();

    // Callback function for quit button input.
    void QuitCallback();

    // Callback functions for camera moving input.
    void MoveCameraUpCallback();
    void MoveCameraDownCallback();
    void MoveCameraLeftCallback();
    void MoveCameraRightCallback();

  private:
    // Background sprite.
    std::unique_ptr<Sprite> bg;

    // User requested quit flag.
    bool quitRequested;

    // Container for all Game Objects instanciated during the game.
    std::vector<std::unique_ptr<GameObject>> objectArray;

    // Tile management and renderization.
    std::unique_ptr<TileMap> tileMap;
};

#endif // STATE_H_