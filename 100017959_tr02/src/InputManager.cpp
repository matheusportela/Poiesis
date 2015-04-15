// @file   InputManager.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Manager for user input

#include "InputManager.h"

std::map<int, int> InputManager::mouseButtonMap =
{
    {SDL_BUTTON_LEFT, MouseButton::Left},
    {SDL_BUTTON_MIDDLE, MouseButton::Middle},
    {SDL_BUTTON_RIGHT, MouseButton::Right},
};

std::map<int, int> InputManager::keyboardButtonMap =
{
    {SDLK_a, KeyboardButton::LowercaseA},
    {SDLK_d, KeyboardButton::LowercaseD},
    {SDLK_s, KeyboardButton::LowercaseS},
    {SDLK_w, KeyboardButton::LowercaseW},
    {SDLK_ESCAPE, KeyboardButton::Esc}
};

InputManager::InputManager()
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

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static InputManager instance;
    return instance;
}

Point& InputManager::GetMousePosition()
{
    return mousePosition;
}

void InputManager::RegisterCallback(std::function<void()> callback,
    InputType::Type inputType, int button)
{
    callbackMap[std::make_pair(inputType, button)] = callback;
}

bool InputManager::HasCallback(InputType::Type inputType, int button)
{
    return (callbackMap.find(std::make_pair(inputType, button))
        != callbackMap.end());
}

void InputManager::ActivateCallback(InputType::Type inputType, int button)
{
    if (HasCallback(inputType, button))
        callbackMap[std::make_pair(inputType, button)]();
}

void InputManager::ProcessInputs()
{
    SDL_Event event;
    int button;
    
    UpdateMousePosition();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                ActivateCallback(InputType::QuitButtonPress);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = InputManager::mouseButtonMap[event.button.button];
                    // It is a press event if it's the first frame in which the
                    // button is hold down
                    if (!mouseDownMap[button])
                        ActivateCallback(InputType::MousePress, button);
                    mouseDownMap[button] = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = InputManager::mouseButtonMap[event.button.button];
                    ActivateCallback(InputType::MouseRelease, button);
                    mouseDownMap[button] = false;
                }
                break;

            case SDL_KEYDOWN:
                if (IsSupportedKeyboardCode(event.key.keysym.sym))
                {
                    button = InputManager::keyboardButtonMap[event.key.keysym.sym];
                    // It is a press event if it's the first frame in which the
                    // button is hold down
                    if (!keyDownMap[button])
                        ActivateCallback(InputType::KeyPress, button);
                    keyDownMap[button] = true;
                }
                break;

            case SDL_KEYUP:
                if (IsSupportedKeyboardCode(event.key.keysym.sym))
                {
                    button = InputManager::keyboardButtonMap[event.key.keysym.sym];
                    ActivateCallback(InputType::KeyRelease, button);
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
            ActivateCallback(InputType::MouseDown, button);
    }

    for (std::map<int, int>::iterator it = keyboardButtonMap.begin();
        it != keyboardButtonMap.end(); ++it)
    {
        button = it->second;
        if(keyDownMap[button])
            ActivateCallback(InputType::KeyDown, button);
    }
}

void InputManager::UpdateMousePosition()
{
    int mouse_x;
    int mouse_y;
    
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mousePosition.Set(mouse_x, mouse_y);
}

bool InputManager::IsSupportedKeyboardCode(int SDLCode)
{
    return (InputManager::keyboardButtonMap.find(SDLCode)
        != InputManager::keyboardButtonMap.end());
}

bool InputManager::IsSupportedMouseCode(int SDLCode)
{
    return (InputManager::mouseButtonMap.find(SDLCode)
        != InputManager::mouseButtonMap.end());
}