// @file   InputManager.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Manager for user input

#include "InputManager.h"

Point& InputManager::GetMousePosition()
{
    return mousePosition;
}

int InputManager::GetPressedKey()
{
    return pressedKey;
}

void InputManager::RegisterCallback(InputType inputType, std::function<void()> callback)
{
    callbackMap[inputType] = callback;
}

bool InputManager::HasCallback(InputType inputType)
{
    std::map<InputType, std::function<void()>>::iterator it = callbackMap.find(inputType);

    return (it != callbackMap.end());
}

void InputManager::ActivateCallback(InputType inputType)
{
    if (HasCallback(inputType))
        callbackMap[inputType]();
}

void InputManager::ProcessInputs()
{
    SDL_Event event;
    
    UpdateMousePosition();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                ActivateCallback(QuitButtonInput);
                break;

            case SDL_MOUSEBUTTONDOWN:
                ActivateCallback(MouseInput);
                break;

            case SDL_KEYDOWN:
                UpdatePressedKey(event.key.keysym.sym);
                ActivateCallback(KeyboardInput);
                break;
        };
    }
}

void InputManager::UpdateMousePosition()
{
    int mouseX;
    int mouseY;
    
    SDL_GetMouseState(&mouseX, &mouseY);
    mousePosition.Set(mouseX, mouseY);
}

void InputManager::UpdatePressedKey(int key)
{
    pressedKey = key;
}