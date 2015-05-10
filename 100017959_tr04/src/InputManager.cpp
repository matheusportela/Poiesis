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

Point InputManager::GetMouseWorldPosition()
{
    return Camera::ScreenToWorldPoint(mousePosition);
}

Point InputManager::GetMouseScreenPosition()
{
    return mousePosition;
}

void InputManager::AddExistingCommand(std::weak_ptr<Command> command,
    InputType::Type inputType, int button)
{
    commandMap[std::make_pair(inputType, button)].push_back(command);
}

void InputManager::AddNewCommand(std::weak_ptr<Command> command,
    InputType::Type inputType, int button)
{
    std::vector<std::weak_ptr<Command>> commands = { command };
    commandMap[std::make_pair(inputType, button)] = commands;
}

void InputManager::RegisterCommand(std::weak_ptr<Command> command,
    InputType::Type inputType, int button)
{
    if (HasCommand(inputType, button))
        AddExistingCommand(command, inputType, button);
    else
        AddNewCommand(command, inputType, button);
}

bool InputManager::HasCommand(InputType::Type inputType, int button)
{
    return (commandMap.find(std::make_pair(inputType, button))
        != commandMap.end());
}

void InputManager::ActivateCommand(std::weak_ptr<Command> command)
{
    if (!command.expired())
    {
        command.lock()->Execute();
    }
    else
    {
        LOG_D("[InputManager] Command expired");
    }
}

void InputManager::ActivateCommands(InputType::Type inputType, int button)
{
    if (HasCommand(inputType, button))
    {
        for (std::pair<std::pair<InputType::Type, int>,
                       std::vector<std::weak_ptr<Command>>> pair : commandMap)
        {
            auto commands = pair.second;

            for (std::weak_ptr<Command> command : commands)
                ActivateCommand(command);
        }
    }
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
                ActivateCommands(InputType::QuitButtonPress);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = InputManager::mouseButtonMap[event.button.button];
                    // It is a press event if it's the first frame in which the
                    // button is hold down
                    if (!mouseDownMap[button])
                        ActivateCommands(InputType::MousePress, button);
                    mouseDownMap[button] = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (IsSupportedMouseCode(event.button.button))
                {
                    button = InputManager::mouseButtonMap[event.button.button];
                    ActivateCommands(InputType::MouseRelease, button);
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
                        ActivateCommands(InputType::KeyPress, button);
                    keyDownMap[button] = true;
                }
                break;

            case SDL_KEYUP:
                if (IsSupportedKeyboardCode(event.key.keysym.sym))
                {
                    button = InputManager::keyboardButtonMap[event.key.keysym.sym];
                    ActivateCommands(InputType::KeyRelease, button);
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
            ActivateCommands(InputType::MouseDown, button);
    }

    for (std::map<int, int>::iterator it = keyboardButtonMap.begin();
        it != keyboardButtonMap.end(); ++it)
    {
        button = it->second;
        if(keyDownMap[button])
            ActivateCommands(InputType::KeyDown, button);
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