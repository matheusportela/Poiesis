// @file   CameraLeftCommand.cpp
// @author Matheus Vieira Portela
// @date   09/05/2015
//
// @brief Move camera position left.

#include "CameraLeftCommand.h"

void CameraLeftCommand::Execute()
{
    Point point(-CFG_GETI("CAMERA_MOVE_DISTANCE"), 0);
    Camera::position.Add(point);
}