// @file   Point.h
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Point in 2-dimensional space

#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include <string>

class Point
{
  public:
    // Empty constructor.
    Point();

    // Initialize with pre-defined (x, y) coordinates.
    Point(float x, float y);

    // Copy constructor.
    Point(Point& other);

    // Getters and setters
    float GetX();
    void SetX(float x);

    float GetY();
    void SetY(float y);

    void Set(float x, float y);

    // Set point coordinates given radius and angle in radians.
    void SetPolar(float r, float ang);

    // Adds two points in Cartesian coordinates.
    void Add(Point& point);

    std::string ToString();

  private:
    // 2-D (x, y) coordinates
    float x;
    float y;
};

#endif // POINT_H_