// Process entities with renderable components and render sprites.

#ifndef DEBUG_SYSTEM_H_
#define DEBUG_SYSTEM_H_

#include <string>

#include "bandit/Engine.h"

class DebugSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void WriteFPS(float dt);
};

#endif // DEBUG_SYSTEM_H_