#include <iostream>
#include <memory.h>

#include "bandit/Engine.h"

#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"
#include "bandit/adapters/sdl/SDLInputAdapter.h"
#include "bandit/adapters/sdl/SDLMusicAdapter.h"
#include "bandit/adapters/sdl/SDLSoundEffectAdapter.h"
#include "bandit/adapters/sdl/SDLSystemAdapter.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"

#include "bandit/core/entity/EntityManager.h"
#include "bandit/core/entity/SystemManager.h"

#include "bandit/core/level/LevelManager.h"

#include "poiesis/level/Level1.h"

int main()
{
    LOG_SET_DEBUG();
    std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();

    std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>();

    std::shared_ptr<SystemManager> systemManager = std::make_shared<SystemManager>();

    levelManager->SetCurrentLevel(
        std::make_shared<Level1>(entityManager, systemManager));

    Engine engine(std::make_shared<SDLSystemAdapter>(),
        std::make_shared<SDLTimerAdapter>(),
        std::make_shared<SDLGraphicsAdapter>(),
        std::make_shared<SDLMusicAdapter>(),
        std::make_shared<SDLSoundEffectAdapter>(),
        std::make_shared<SDLInputAdapter>(),
        entityManager,
        levelManager,
        systemManager);

    engine.Run();
    
    return 0;
}