// Implementation of InputAdapter interface using SDL.

#ifndef SDL_INPUT_ADAPTER_H_
#define SDL_INPUT_ADAPTER_H_

#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL.h>

#include "bandit/adapters/InputAdapter.h"

class SDLInputAdapter : public InputAdapter
{
  public:
    void ProcessInputs();
    bool CheckInputOccurred(InputType::Type inputType, int button = 0);

  private:
    void PushOccurredInput(InputType::Type inputType, int button = 0);

    // Inputs that occurred since the last reset.
    std::vector<std::pair<InputType::Type, int>> occurredInputs;
};

#endif // SDL_INPUT_ADAPTER_H_