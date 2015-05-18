#include "bandit/adapters/sdl/SDLInputAdapter.h"

void SDLInputAdapter::ProcessInputs()
{
    SDL_Event event;
    int button;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                PushOccurredInput(InputType::QuitButtonPress);
                break;
        }
    }
}

void SDLInputAdapter::PushOccurredInput(InputType::Type inputType, int button)
{
    occurredInputs.push_back(std::make_pair(inputType, button));
}

bool SDLInputAdapter::CheckInputOccurred(InputType::Type inputType, int button)
{
    std::pair<InputType::Type, int> input = std::make_pair(inputType, button);

    return (std::find(occurredInputs.begin(), occurredInputs.end(), input) != occurredInputs.end());
}