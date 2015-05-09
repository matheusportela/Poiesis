// @file   CommandFactory.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Creates new input commands.

#include "CommandFactory.h"

std::shared_ptr<Command> CommandFactory::CreateCameraUpCommand(
    InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command = std::make_shared<CameraUpCommand>();
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraDownCommand(
    InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command = std::make_shared<CameraDownCommand>();
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraLeftCommand(
    InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command = std::make_shared<CameraLeftCommand>();
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraRightCommand(
    InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command = std::make_shared<CameraRightCommand>();
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateQuitCommand(State* parent,
    InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command = std::make_shared<QuitCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsShootCommand(
    Penguins* parent, InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsShootCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsSpeedUpCommand(
    Penguins* parent, InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsSpeedUpCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsSlowDownCommand(
    Penguins* parent, InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsSlowDownCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsLeftRotationCommand(
    Penguins* parent, InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsLeftRotationCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsRightRotationCommand(
    Penguins* parent, InputType::Type inputType, int button)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsRightRotationCommand>(parent);
    InputManager::GetInstance().RegisterCommand(command, inputType, button);
    return command;
}