// Implementation of InputAdapter interface using SDL.

#ifndef SDL_INPUT_ADAPTER_H_
#define SDL_INPUT_ADAPTER_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include <SDL.h>

#include "bandit/adapters/InputAdapter.h"

class SDLInputAdapter : public InputAdapter
{
  public:
    SDLInputAdapter();
    void ProcessInputs();
    bool CheckInputOccurred(InputType::Type inputType, int button = 0);

  private:
    // Registers that a type of input occurred.
    void PushOccurredInput(InputType::Type inputType, int button = 0);

    bool IsSupportedKeyboardCode(int SDLCode);
    bool IsSupportedMouseCode(int SDLCode);

    // Maps SDL mouse button to InputManager mouse button.
    static std::map<int, int> mouseButtonMap;

    // Maps SDL keyboard button to InputManager keyboard button.
    static std::map<int, int> keyboardButtonMap;

    // Holds whether some key is pressed down.
    std::map<int, int> keyDownMap;

    // Holds whether some mouse button is pressed down.
    std::map<int, int> mouseDownMap;

    // Inputs that occurred since the last reset.
    std::vector<std::pair<InputType::Type, int>> occurredInputs;
};

#endif // SDL_INPUT_ADAPTER_H_