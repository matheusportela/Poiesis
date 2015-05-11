// @file   State.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game state class definition
//
// Definition of class for a game-specific logic.

#ifndef STATE_H_
#define STATE_H_

#include <memory>
#include <vector>

#include "Camera.h"
#include "CollisionSimulator.h"
#include "Command.h"
#include "CommandFactory.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"

// This class provides game-specific logic methods.
class State
{
  public:
    // Initializes the game state.
    State();

    // Initialize Penguins game object.
    void InitializePenguins();

    // Initialize Alien game object.
    void InitializeAlien();

    // Configures commands for all relevant user input type in the game.
    void ConfigureInputCommands();

    // Updates game state after a delta time in seconds.
    void Update(float dt);

    // Renders game.
    void Render();

    // Renders all sprites that stays behind the game characters.
    void RenderBottomTiles();

    // Renders all sprites that stays above the game characters.
    void RenderTopTiles();

    // Returns true if quit was requested by the user.
    bool IsQuitRequested();

    // Set quit requested as true.
    void SetQuitRequested();

  private:
    // Background sprite.
    std::unique_ptr<Sprite> bg;

    // User requested quit flag.
    bool quitRequested;

    // Tile management and renderization.
    std::unique_ptr<TileMap> tileMap;

    // Commands.
    std::shared_ptr<Command> quitButtonCommand;
    std::shared_ptr<Command> quitEscCommand;
    std::shared_ptr<Command> cameraUpCommand;
    std::shared_ptr<Command> cameraDownCommand;
    std::shared_ptr<Command> cameraLeftCommand;
    std::shared_ptr<Command> cameraRightCommand;
};

#endif // STATE_H_