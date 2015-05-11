// @file   CameraDownCommand.h
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position down.

#ifndef CAMERA_DOWN_COMMAND_H_
#define CAMERA_DOWN_COMMAND_H_

#include "Camera.h"
#include "ConfigParser.h"
#include "Command.h"
#include "Point.h"

class CameraDownCommand : public Command
{
  public:
    void Execute();
};

#endif // CAMERA_DOWN_COMMAND_H_