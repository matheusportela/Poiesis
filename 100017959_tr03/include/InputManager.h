// @file   InputManager.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Manager for user input
//
// Input manager is the responsible for polling SDL for user input. After doing
// so, if any input happened, it calls the registered callback function for the
// input type, if any is present.
// This provides a loose coupling, easily allowing methods to be independently
// called for UI processing.

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <functional>
#include <map>
#include <utility>

#include <SDL.h>

#include "Camera.h"
#include "Command.h"
#include "Logger.h"
#include "Point.h"

#define REGISTER_INPUT_TYPE_CALLBACK(method, key) \
    LOG_D("[InputManager] Registering callback - function: " << #method << \
        ", key: " << #key); \
    InputManager::GetInstance().RegisterCallback(std::bind(&method, this), key);

#define REGISTER_INPUT_KEY_CALLBACK(method, type, key) \
    LOG_D("[InputManager] Registering callback - function: " << #method << \
        ", type: " << #type << ", key: " << #key); \
    InputManager::GetInstance().RegisterCallback(std::bind(&method, this), type, key);


// All supported types of input.
namespace InputType
{
    enum Type
    {
        MousePress,
        MouseRelease,
        MouseDown,
        KeyPress,
        KeyRelease,
        KeyDown,
        QuitButtonPress,
    };
}

// All supported types of mouse input.
namespace MouseButton
{
    enum Button
    {
        Left,
        Middle,
        Right,
    };
}

// All supported types of keyboard input.
namespace KeyboardButton
{
    enum Button
    {
        LowercaseA,
        LowercaseB,
        LowercaseC,
        LowercaseD,
        LowercaseE,
        LowercaseF,
        LowercaseG,
        LowercaseH,
        LowercaseI,
        LowercaseJ,
        LowercaseK,
        LowercaseL,
        LowercaseM,
        LowercaseN,
        LowercaseO,
        LowercaseP,
        LowercaseQ,
        LowercaseR,
        LowercaseS,
        LowercaseT,
        LowercaseU,
        LowercaseV,
        LowercaseW,
        LowercaseX,
        LowercaseY,
        LowercaseZ,
        Number0,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,
        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,
        Esc,
        Space,
    };
}

class InputManager
{
  public:
    // Singleton pattern.
    static InputManager& GetInstance();

    // Gets mouse position with respect to the world coordinates.
    Point GetMouseWorldPosition();

    // Gets mouse position with respect to the screen coordinates.
    Point GetMouseScreenPosition();

    // Register a function to be called whenever an input of type inputType
    // happens. The callback function must return void and receive no arguments.
    void RegisterCallback(std::function<void()> callback,
        InputType::Type inputType, int button = 0);

    // Register a command to be executed whenever an input of the given type
    // happens.
    void RegisterCommand(std::weak_ptr<Command> command,
        InputType::Type inputType, int button);

    // Checks whether an input type has a callback function.
    bool HasCallback(InputType::Type inputType, int button = 0);

    // Checks whether an input type has registered commands.
    bool HasCommand(InputType::Type inputType, int button = 0);

    // Calls the callback function of an input type.
    void ActivateCallback(InputType::Type inputType, int button = 0);

    // Executes the registered command to the input type.
    void ActivateCommand(InputType::Type inputType, int button = 0);

    // Activates callback functions for specified input types.
    void ProcessInputs();

    // Get mouse position and store.
    void UpdateMousePosition();

    bool IsSupportedKeyboardCode(int SDLCode);
    bool IsSupportedMouseCode(int SDLCode);

  private:
    // Constructor.
    InputManager();
    ~InputManager();

    // Maps SDL mouse button to InputManager mouse button.
    static std::map<int, int> mouseButtonMap;

    // Maps SDL keyboard button to InputManager keyboard button.
    static std::map<int, int> keyboardButtonMap;

    // Container for callback functions.
    std::map<std::pair<InputType::Type, int>, std::function<void()>> callbackMap;

    // Current mouse position.
    Point mousePosition;

    // Holds whether some key is pressed down.
    std::map<int, int> keyDownMap;

    // Holds whether some mouse button is pressed down.
    std::map<int, int> mouseDownMap;





    // Container for commands.
    std::map<std::pair<InputType::Type, int>, std::weak_ptr<Command>> commandMap;
};

#endif // INPUT_MANAGER_H_