// @file   CameraUpCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position up.

#include "CameraUpCommand.h"

void CameraUpCommand::Execute()
{
    Point point(0, -CFG_GETI("CAMERA_MOVE_DISTANCE"));
    Camera::position.Add(point);
}