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
#include "FinishCommand.h"
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
    static std::shared_ptr<Command> CreateCameraUpCommand();

    static std::shared_ptr<Command> CreateCameraDownCommand();

    static std::shared_ptr<Command> CreateCameraLeftCommand();

    static std::shared_ptr<Command> CreateCameraRightCommand();

    static std::shared_ptr<Command> CreateFinishCommand(State* parent);
    
    static std::shared_ptr<Command> CreateQuitCommand(State* parent);

    static std::shared_ptr<Command> CreatePenguinsShootCommand(
        Penguins* parent);

    static std::shared_ptr<Command> CreatePenguinsSpeedUpCommand(
        Penguins* parent);

    static std::shared_ptr<Command> CreatePenguinsSlowDownCommand(
        Penguins* parent);
    
    static std::shared_ptr<Command> CreatePenguinsLeftRotationCommand(
        Penguins* parent);

    static std::shared_ptr<Command> CreatePenguinsRightRotationCommand(
        Penguins* parent);
};

#endif // COMMAND_FACTORY_H_