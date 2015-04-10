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

#ifndef INPUT_TYPE_H_
#define INPUT_TYPE_H_

// All types of input used by the game.
namespace InputType
{
    enum Type
    {
        MouseInput,
        KeyboardInput,
        QuitButtonInput
    };
}

#endif // INPUT_TYPE_H_