// @file   StageState.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game level
//
// Definition of the only level for the game.

#ifndef STAGE_STATE_H_
#define STAGE_STATE_H_

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
#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "TileMap.h"
#include "TileSet.h"

// This class provides game-specific logic methods.
class StageState : public State
{
  public:
    // Initializes the game state.
    StageState();

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

    void Pause() {};
    void Resume() {};

    static InputManager inputManager;

  private:
    // Background sprite.
    std::unique_ptr<Sprite> bg;

    // Background music.
    std::unique_ptr<Music> background_music;

    // Tile management and renderization.
    std::unique_ptr<TileMap> tileMap;

    // Commands.
    std::shared_ptr<Command> quitCommand;
    std::shared_ptr<Command> cameraUpCommand;
    std::shared_ptr<Command> cameraDownCommand;
    std::shared_ptr<Command> cameraLeftCommand;
    std::shared_ptr<Command> cameraRightCommand;
};

#endif // STAGE_STATE_H_