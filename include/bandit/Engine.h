// Run basic engine initialization and shutdown methods.
//
// Some modules must be initialized in order to provide functionality to the
// higher-level modules. Also, they must be properly shutdown, avoiding memory
// leaks and system crashing.

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <memory>

#include "bandit/adapters/AudioAdapter.h"
#include "bandit/adapters/GraphicsAdapter.h"
#include "bandit/adapters/InputAdapter.h"
#include "bandit/adapters/SystemAdapter.h"
#include "bandit/adapters/TimerAdapter.h"
#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"
#include "bandit/adapters/sdl/SDLInputAdapter.h"
#include "bandit/adapters/sdl/SDLMusicAdapter.h"
#include "bandit/adapters/sdl/SDLSoundEffectAdapter.h"
#include "bandit/adapters/sdl/SDLSystemAdapter.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"

#include "bandit/core/Log.h"
#include "bandit/core/Random.h"
#include "bandit/core/math/Circle.h"
#include "bandit/core/math/LineSegment.h"
#include "bandit/core/math/Rectangle.h"
#include "bandit/core/math/Vector.h"
#include "bandit/core/parser/ConfigParser.h"
#include "bandit/core/time/PeriodicTimer.h"
#include "bandit/core/time/Timer.h"

#include "bandit/entity/Component.h"
#include "bandit/entity/Entity.h"
#include "bandit/entity/EntityManager.h"
#include "bandit/entity/System.h"
#include "bandit/entity/SystemManager.h"

#include "bandit/level/LevelManager.h"

#define BANDIT_ENGINE_INIT() \
    Engine::GetInstance().Initialize( \
        std::make_shared<SDLSystemAdapter>(), \
        std::make_shared<SDLTimerAdapter>(), \
        std::make_shared<SDLGraphicsAdapter>(), \
        std::make_shared<SDLMusicAdapter>(), \
        std::make_shared<SDLSoundEffectAdapter>(), \
        std::make_shared<SDLInputAdapter>(), \
        std::make_shared<EntityManager>(), \
        std::make_shared<LevelManager>(), \
        std::make_shared<SystemManager>())

#define BANDIT_ENGINE_SHUTDOWN() \
    Engine::GetInstance().Shutdown()

class Engine
{
  public:
    static Engine& GetInstance();

    std::shared_ptr<GraphicsAdapter> GetGraphicsAdapter();
    std::shared_ptr<InputAdapter> GetInputAdapter();
    std::shared_ptr<EntityManager> GetEntityManager();
    std::shared_ptr<SystemManager> GetSystemManager();
    std::shared_ptr<LevelManager> GetLevelManager();

    // Initializes engine adapters and managers.
    void Initialize(
        std::shared_ptr<SystemAdapter> systemAdapter,
        std::shared_ptr<TimerAdapter> timerAdapter,
        std::shared_ptr<GraphicsAdapter> graphicsAdapter,
        std::shared_ptr<AudioAdapter> musicAdapter,
        std::shared_ptr<AudioAdapter> soundEffectAdapter,
        std::shared_ptr<InputAdapter> inputAdapter,
        std::shared_ptr<EntityManager> entityManager,
        std::shared_ptr<LevelManager> levelManager,
        std::shared_ptr<SystemManager> systemManager);

    // Shutdown engine adapters and managers.
    void Shutdown();

    void CreateWindow(std::string title, int height, int width);
    void SetCurrentLevel(std::shared_ptr<Level> level);
    void SetNextLevel(std::shared_ptr<Level> level);
    std::shared_ptr<Entity> CreateEntity();
    void AddComponent(std::shared_ptr<Component> component,
        std::shared_ptr<Entity> entity);
    void AddSystem(std::shared_ptr<System> system);

    // Executes the engine main loop.
    void Run();

  private:
    // Singleton pattern.
    Engine() {};
    Engine(const Engine&) = delete;
    void operator=(const Engine&) = delete;

    // Calculates the amount of time the engine can sleep in this frame in
    // order to maintain a constant frame rate.
    float CalculateSleepTime(float currentFrameRate);

    std::shared_ptr<SystemAdapter> systemAdapter;
    std::shared_ptr<TimerAdapter> timerAdapter;
    std::shared_ptr<GraphicsAdapter> graphicsAdapter;
    std::shared_ptr<AudioAdapter> musicAdapter;
    std::shared_ptr<AudioAdapter> soundEffectAdapter;
    std::shared_ptr<InputAdapter> inputAdapter;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<LevelManager> levelManager;
    std::shared_ptr<SystemManager> systemManager;
};

#endif // ENGINE_H_