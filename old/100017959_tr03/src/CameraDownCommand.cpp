// @file   CameraDownCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position down.

#include "CameraDownCommand.h"

void CameraDownCommand::Execute()
{
    Point point(0, CFG_GETI("CAMERA_MOVE_DISTANCE"));
    Camera::position.Add(point);
}