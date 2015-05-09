// @file   CameraUpCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position up.

#ifndef CAMERA_UP_COMMAND_H_
#define CAMERA_UP_COMMAND_H_

#include "Camera.h"
#include "ConfigParser.h"
#include "Command.h"
#include "Point.h"

class CameraUpCommand : public Command
{
  public:
    void Execute();
};

#endif // CAMERA_UP_COMMAND_H_