// Stores data relevant for HUD buttons.

#ifndef BUTTON_COMPONENT_H_
#define BUTTON_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ButtonComponent : public Component
{
  public:
    ButtonComponent(Rectangle rectangle = Rectangle(0, 0, 100, 100));
    std::string GetComponentClass();

    Rectangle GetRectangle();
    void SetRectangle(Rectangle rectangle);

  private:
    // Holds the button position and dimensions.
    Rectangle rectangle;
};

#endif // BUTTON_COMPONENT_H_