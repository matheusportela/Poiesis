// Implementation of InputAdapter interface using SDL.

#ifndef SDL_INPUT_ADAPTER_H_
#define SDL_INPUT_ADAPTER_H_

#include <iostream>
#include <vector>

#include <SDL.h>

#include "bandit/adapters/InputAdapter.h"

class SDLInputAdapter : public InputAdapter
{
  public:
    void ProcessInputs();
    bool CheckInputOccurred(InputType::Type inputType, int button);

  private:
    // Inputs that occurred since the last reset.
    // std::vector<InputType::Type, int> occurredInputs;
};

#endif // SDL_INPUT_ADAPTER_H_