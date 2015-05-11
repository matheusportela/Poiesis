// @file   StageState.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game level

#include "StageState.h"
#include "Game.h"
#include "EndState.h"

InputManager StageState::inputManager;

StageState::StageState()
{
    quitRequested = false;
    playingMusic = false;
    bg = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("STATE_BACKGROUND")));
    background_music = std::unique_ptr<Music>(new Music(CFG_GETP("STATE_MUSIC")));
    std::unique_ptr<TileSet> tileSet(new TileSet(CFG_GETI("TILE_WIDTH"),
        CFG_GETI("TILE_HEIGHT"), CFG_GETP("TILE_SET")));
    tileMap = std::unique_ptr<TileMap>(new TileMap(CFG_GETP("TILE_MAP"),
        std::move(tileSet)));

    InitializePenguins();
    InitializeAlien();

    ConfigureInputCommands();
}

StageState::~StageState()
{
    Game::GetInstance()->AddState(std::unique_ptr<State>(new EndState(win)));
    GameObjectManager::GetInstance().DeleteAllObjects();
    inputManager.Clear();
}

void StageState::InitializePenguins()
{
    Point position(CFG_GETI("PENGUINS_INITIAL_X"),
        CFG_GETI("PENGUINS_INITIAL_Y"));
    GameObjectFactory::CreatePenguins(position, "player");
    Camera::Follow(GameObjectManager::GetInstance().GetObject("player"));
}

void StageState::InitializeAlien()
{
    Point position(CFG_GETI("ALIEN_INITIAL_X"),
        CFG_GETI("ALIEN_INITIAL_Y"));
    int numMinions = CFG_GETI("ALIEN_NUM_MINIONS");
    GameObjectFactory::CreateAlien(position, numMinions, "alien");
}

void StageState::ConfigureInputCommands()
{
    quitCommand = CommandFactory::CreateQuitCommand(this);
    inputManager.RegisterCommand(quitCommand, InputType::QuitButtonPress);
    inputManager.RegisterCommand(quitCommand, InputType::KeyPress, KeyboardButton::Esc);

    cameraUpCommand = CommandFactory::CreateCameraUpCommand();
    inputManager.RegisterCommand(cameraUpCommand, InputType::KeyDown, KeyboardButton::ArrowUp);

    cameraDownCommand = CommandFactory::CreateCameraDownCommand();
    inputManager.RegisterCommand(cameraDownCommand, InputType::KeyDown, KeyboardButton::ArrowDown);
    
    cameraLeftCommand = CommandFactory::CreateCameraLeftCommand();
    inputManager.RegisterCommand(cameraLeftCommand, InputType::KeyDown, KeyboardButton::ArrowLeft);

    cameraRightCommand = CommandFactory::CreateCameraRightCommand();
    inputManager.RegisterCommand(cameraRightCommand, InputType::KeyDown, KeyboardButton::ArrowRight);
}

void StageState::CheckEndConditions()
{
    auto penguins = GameObjectManager::GetInstance().GetObjects("player");
    auto aliens = GameObjectManager::GetInstance().GetObjects("alien");
    
    if (penguins.size() == 0)
    {
        LOG_I("[StageState] Lose");
        win = false;
        SetFinished();
    }

    if (aliens.size() == 0)
    {
        LOG_I("[StageState] Win");
        win = true;
        SetFinished();
    }
}

void StageState::Update(float dt)
{
    if (!playingMusic)
    {
        playingMusic = true;
        background_music->Play();
    }

    Camera::Update(dt);
    inputManager.ProcessInputs();
    GameObjectManager::GetInstance().Update(dt);
    CollisionSimulator::Collide();
    CheckEndConditions();
}

void StageState::Render()
{
    RenderBottomTiles();
    GameObjectManager::GetInstance().Render();
    RenderTopTiles();
}

void StageState::RenderBottomTiles()
{
    Point bg_point(0, 0);

    // Movement illusion requires background to move in the direction opposite
    // to the camera. Hence, we negate it's position.
    Point tile_map_point = Camera::position;
    tile_map_point.Negate();

    bg->Render(bg_point);
    tileMap->RenderBaseLayer(tile_map_point);
}

void StageState::RenderTopTiles()
{
    // Movement illusion requires background to move in the direction opposite
    // to the camera. Hence, we negate it's position.
    Point tile_map_point = Camera::position;
    tile_map_point.Negate();
    
    tileMap->RenderUpperLayers(tile_map_point);
}