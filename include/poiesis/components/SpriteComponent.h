// Component that holds sprite information to be rendered.

#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

#include <string>

#include "bandit/core/entity/Component.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent(std::string filename);
    std::string GetComponentClass();

    std::string filename;
};

#endif // SPRITE_COMPONENT_H_