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
    Rect(const Point& point);

    // Initialize with pre-defined (x, y) coordinates, width and height.
    Rect(const Point& point, float w, float h);

    // Getters and setters
    Point GetPoint() const;
    void SetPoint(const Point& point);

    float GetW() const;
    void SetW(float w);

    float GetH() const;
    void SetH(float h);

    void Set(const Point& point);
    void Set(const Point& point, float w, float h);

    // Sets rectangle with it's center at (centerX, centerY)
    void SetCenter(const Point& centerPoint, float w, float h);
    Point GetCenter() const;

    // Returns string with rectangle's coordinates and dimensions.
    std::string ToString() const;

    // Checks whether a given point is inside the rectangle's dimensions.
    bool IsInside(const Point& point) const;

  private:
    // 2-D (x, y) coordinates corresponding to the upper-left corner.
    Point point;

    // Rectangle width
    float w;

    // Rectangle height
    float h;
};

#endif // RECT_H_