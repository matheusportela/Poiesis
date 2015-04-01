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

#include <SDL.h>

#include "InputType.h"
#include "Point.h"

class InputManager
{
  public:
    // Getters and setters.
    Point& GetMousePosition();
    int GetPressedKey();

    // Register a function to be called whenever an input of type inputType
    // happens. The callback function must return void and receive no arguments.
    void RegisterCallback(InputType::Type inputType, std::function<void()> callback);

    // Checks whether an input type has a callback function.
    bool HasCallback(InputType::Type inputType);

    // Calls the callback function of an input type.
    void ActivateCallback(InputType::Type inputType);

    // Activates callback functions for specified input types.
    void ProcessInputs();

    // Get mouse position and store.
    void UpdateMousePosition();

    // Get pressed key and store.
    void UpdatePressedKey(int key);

  private:
    // Container for callback functions.
    std::map<InputType::Type, std::function<void()>> callbackMap;

    // Current mouse position.
    Point mousePosition;

    // Last pressed key.
    int pressedKey;
};

#endif // INPUT_MANAGER_H_