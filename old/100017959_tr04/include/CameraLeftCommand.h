// @file   CameraLeftCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position left.

#ifndef CAMERA_LEFT_COMMAND_H_
#define CAMERA_LEFT_COMMAND_H_

#include "Camera.h"
#include "ConfigParser.h"
#include "Command.h"
#include "Point.h"

class CameraLeftCommand : public Command
{
  public:
    void Execute();
};

#endif // CAMERA_LEFT_COMMAND_H_