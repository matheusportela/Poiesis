// @file   CameraRightCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position right.

#ifndef CAMERA_RIGHT_COMMAND_H_
#define CAMERA_RIGHT_COMMAND_H_

#include "Camera.h"
#include "ConfigParser.h"
#include "Command.h"
#include "Point.h"

class CameraRightCommand : public Command
{
  public:
    void Execute();
};

#endif // CAMERA_RIGHT_COMMAND_H_