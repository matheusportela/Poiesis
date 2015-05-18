#include "bandit/adapters/sdl/SDLInputAdapter.h"

std::map<int, int> SDLInputAdapter::mouseButtonMap =
{
    {SDL_BUTTON_LEFT, MouseButton::Left},
    {SDL_BUTTON_MIDDLE, MouseButton::Middle},
    {SDL_BUTTON_RIGHT, MouseButton::Right},
};

std::map<int, int> SDLInputAdapter::keyboardButtonMap =
{
    {SDLK_a, KeyboardButton::LowercaseA},
    {SDLK_b, KeyboardButton::LowercaseB},
    {SDLK_c, KeyboardButton::LowercaseC},
    {SDLK_d, KeyboardButton::LowercaseD},
    {SDLK_e, KeyboardButton::LowercaseE},
    {SDLK_f, KeyboardButton::LowercaseF},
    {SDLK_g, KeyboardButton::LowercaseG},
    {SDLK_h, KeyboardButton::LowercaseH},
    {SDLK_i, KeyboardButton::LowercaseI},
    {SDLK_j, KeyboardButton::LowercaseJ},
    {SDLK_k, KeyboardButton::LowercaseK},
    {SDLK_l, KeyboardButton::LowercaseL},
    {SDLK_m, KeyboardButton::LowercaseM},
    {SDLK_n, KeyboardButton::LowercaseN},
    {SDLK_o, KeyboardButton::LowercaseO},
    {SDLK_p, KeyboardButton::LowercaseP},
    {SDLK_q, KeyboardButton::LowercaseQ},
    {SDLK_r, KeyboardButton::LowercaseR},
    {SDLK_s, KeyboardButton::LowercaseS},
    {SDLK_t, KeyboardButton::LowercaseT},
    {SDLK_u, KeyboardButton::LowercaseU},
    {SDLK_v, KeyboardButton::LowercaseV},
    {SDLK_w, KeyboardButton::LowercaseW},
    {SDLK_x, KeyboardButton::LowercaseX},
    {SDLK_y, KeyboardButton::LowercaseY},
    {SDLK_z, KeyboardButton::LowercaseZ},
    {SDLK_0, KeyboardButton::Number0},
    {SDLK_1, KeyboardButton::Number1},
    {SDLK_2, KeyboardButton::Number2},
    {SDLK_3, KeyboardButton::Number3},
    {SDLK_4, KeyboardButton::Number4},
    {SDLK_5, KeyboardButton::Number5},
    {SDLK_6, KeyboardButton::Number6},
    {SDLK_7, KeyboardButton::Number7},
    {SDLK_8, KeyboardButton::Number8},
    {SDLK_9, KeyboardButton::Number9},
    {SDLK_UP, KeyboardButton::ArrowUp},
    {SDLK_DOWN, KeyboardButton::ArrowDown},
    {SDLK_LEFT, KeyboardButton::ArrowLeft},
    {SDLK_RIGHT, KeyboardButton::ArrowRight},
    {SDLK_LSHIFT, KeyboardButton::LeftShift},
    {SDLK_RSHIFT, KeyboardButton::RightShift},
    {SDLK_LCTRL, KeyboardButton::LeftCtrl},
    {SDLK_RCTRL, KeyboardButton::RightCtrl},
    {SDLK_ESCAPE, KeyboardButton::Esc},
    {SDLK_SPACE, KeyboardButton::Space},
};

SDLInputAdapter::SDLInputAdapter()
{
    std::map<int, int>::iterator it;
    int button;

    for (it = mouseButtonMap.begin(); it != mouseButtonMap.end(); ++it)
    {
        button = it->second;
        mouseDownMap[button] = false;
    }

    for (it = keyboardButtonMap.begin(); it != keyboardButtonMap.end(); ++it)
    {
        button = it->second;
        keyDownMap[button] = false;
    }
}

void SDLInputAdapter::ProcessInputs()
{
    SDL_Event event;
    int button;

    occurredInputs.clear();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                PushOccurredInput(InputType::QuitButtonPress);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = SDLInputAdapter::mouseButtonMap[event.button.button];
                    // It is a press event if it's the first frame in which the
                    // button is hold down
                    if (!mouseDownMap[button])
                        PushOccurredInput(InputType::MousePress, button);
                    mouseDownMap[button] = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = SDLInputAdapter::mouseButtonMap[event.button.button];
                    PushOccurredInput(InputType::MouseRelease, button);
                    mouseDownMap[button] = false;
                }
                break;

            case SDL_KEYDOWN:
                if (IsSupportedKeyboardCode(event.key.keysym.sym))
                {
                    button = SDLInputAdapter::keyboardButtonMap[event.key.keysym.sym];
                    // It is a press event if it's the first frame in which the
                    // button is hold down
                    if (!keyDownMap[button])
                        PushOccurredInput(InputType::KeyPress, button);
                    keyDownMap[button] = true;
                }
                break;

            case SDL_KEYUP:
                if (IsSupportedKeyboardCode(event.key.keysym.sym))
                {
                    button = SDLInputAdapter::keyboardButtonMap[event.key.keysym.sym];
                    PushOccurredInput(InputType::KeyRelease, button);
                    keyDownMap[button] = false;
                }
                break;
        };
    }

    // Process all buttons that are down
    for (std::map<int, int>::iterator it = mouseButtonMap.begin();
        it != mouseButtonMap.end(); ++it)
    {
        button = it->second;
        if(mouseDownMap[button])
            PushOccurredInput(InputType::MouseDown, button);
    }

    for (std::map<int, int>::iterator it = keyboardButtonMap.begin();
        it != keyboardButtonMap.end(); ++it)
    {
        button = it->second;
        if(keyDownMap[button])
            PushOccurredInput(InputType::KeyDown, button);
    }
}

bool SDLInputAdapter::IsSupportedKeyboardCode(int SDLCode)
{
    return (keyboardButtonMap.find(SDLCode) != keyboardButtonMap.end());
}

bool SDLInputAdapter::IsSupportedMouseCode(int SDLCode)
{
    return (mouseButtonMap.find(SDLCode) != mouseButtonMap.end());
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