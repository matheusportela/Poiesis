// @file   CommandFactory.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Creates new input commands.

#include "CommandFactory.h"

std::shared_ptr<Command> CommandFactory::CreateCameraUpCommand()
{
    std::shared_ptr<Command> command = std::make_shared<CameraUpCommand>();
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraDownCommand()
{
    std::shared_ptr<Command> command = std::make_shared<CameraDownCommand>();
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraLeftCommand()
{
    std::shared_ptr<Command> command = std::make_shared<CameraLeftCommand>();
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateCameraRightCommand()
{
    std::shared_ptr<Command> command = std::make_shared<CameraRightCommand>();
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateFinishCommand(State* parent)
{
    std::shared_ptr<Command> command = std::make_shared<FinishCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreateQuitCommand(State* parent)
{
    std::shared_ptr<Command> command = std::make_shared<QuitCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsShootCommand(
    Penguins* parent)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsShootCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsSpeedUpCommand(
    Penguins* parent)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsSpeedUpCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsSlowDownCommand(
    Penguins* parent)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsSlowDownCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsLeftRotationCommand(
    Penguins* parent)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsLeftRotationCommand>(parent);
    return command;
}

std::shared_ptr<Command> CommandFactory::CreatePenguinsRightRotationCommand(
    Penguins* parent)
{
    std::shared_ptr<Command> command =
        std::make_shared<PenguinsRightRotationCommand>(parent);
    return command;
}