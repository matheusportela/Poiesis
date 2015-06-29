// Stores data relevant for HUD buttons.

#ifndef BUTTON_COMPONENT_H_
#define BUTTON_COMPONENT_H_

#include <functional>
#include <string>

#include "bandit/Engine.h"

class ButtonComponent : public Component
{
  public:
    ButtonComponent(Rectangle rectangle, std::function<void()> callback);
    std::string GetComponentClass();

    Rectangle GetRectangle();
    void SetRectangle(Rectangle rectangle);

    std::function<void()> GetCallback();
    void SetCallback(std::function<void()> callback);

  private:
    // Holds the button position and dimensions.
    Rectangle rectangle;

    // Holds the callback function that is called when the button is pressed.
    std::function<void()> callback;
};

#endif // BUTTON_COMPONENT_H_