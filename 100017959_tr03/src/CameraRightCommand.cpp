// @file   CameraRightCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position right.

#include "CameraRightCommand.h"

void CameraRightCommand::Execute()
{
    Point point(CFG_GETI("CAMERA_MOVE_DISTANCE"), 0);
    Camera::position.Add(point);
}