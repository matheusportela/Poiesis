// @file   CommandFactory.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Creates new input commands.

#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include <memory>

#include "Command.h"
#include "CameraDownCommand.h"
#include "CameraLeftCommand.h"
#include "CameraRightCommand.h"
#include "CameraUpCommand.h"
#include "InputManager.h"
#include "PenguinsShootCommand.h"
#include "PenguinsLeftRotationCommand.h"
#include "PenguinsRightRotationCommand.h"
#include "PenguinsSlowDownCommand.h"
#include "PenguinsSpeedUpCommand.h"
#include "QuitCommand.h"

class Penguins;
class State;

class CommandFactory : public Command
{
  public:
    static std::shared_ptr<Command> CreateCameraUpCommand(
        InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreateCameraDownCommand(
        InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreateCameraLeftCommand(
        InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreateCameraRightCommand(
        InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreateQuitCommand(State* parent,
        InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreatePenguinsShootCommand(
        Penguins* parent, InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreatePenguinsSpeedUpCommand(
        Penguins* parent, InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreatePenguinsSlowDownCommand(
        Penguins* parent, InputType::Type inputType, int button = 0);
    
    static std::shared_ptr<Command> CreatePenguinsLeftRotationCommand(
        Penguins* parent, InputType::Type inputType, int button = 0);

    static std::shared_ptr<Command> CreatePenguinsRightRotationCommand(
        Penguins* parent, InputType::Type inputType, int button = 0);
};

#endif // COMMAND_FACTORY_H_