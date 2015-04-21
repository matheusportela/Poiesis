// @file   Rect.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Rectangle in 2-dimensional space

#ifndef RECT_H_
#define RECT_H_

#include <string>

#include "Point.h"

class Rect
{
  public:
    // Empty constructor.
    Rect();

    // Initialize with pre-defined (x, y) coordinates and zero width and height.
    Rect(Point point);

    // Initialize with pre-defined (x, y) coordinates, width and height.
    Rect(Point point, float w, float h);

    // Getters and setters
    Point GetPoint();
    void SetPoint(Point point);

    float GetW();
    void SetW(float w);

    float GetH();
    void SetH(float h);

    void Set(Point point);
    void Set(Point point, float w, float h);

    // Sets rectangle with it's center at (centerX, centerY)
    void SetCenter(Point centerPoint, float w, float h);
    Point GetCenter();

    // Returns string with rectangle's coordinates and dimensions.
    std::string ToString();

    // Checks whether a given point is inside the rectangle's dimensions.
    bool IsInside(Point point);

  private:
    // 2-D (x, y) coordinates corresponding to the upper-left corner.
    Point point;

    // Rectangle width
    float w;

    // Rectangle height
    float h;
};

#endif // RECT_H_