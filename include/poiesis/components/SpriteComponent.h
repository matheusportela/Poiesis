// Component that holds sprite information to be rendered.

#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent(std::string filename, bool centered = true, float scale = 1);
    std::string GetComponentClass();

    std::string GetFilename();
    void SetFilename(std::string filename);

    bool GetCentered();
    void SetCentered(bool centered);

    float GetScale();
    void SetScale(float scale);

  private:
    // Holds the file containing the image to be displayed.
    std::string filename;

    // Holds whether the image should be displayed centered.
    bool centered;

    float scale;
};

#endif // SPRITE_COMPONENT_H_