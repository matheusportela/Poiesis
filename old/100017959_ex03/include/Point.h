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

    // Initializes with pre-defined (x, y) coordinates.
    Point(float x, float y);

    // Copy constructor.
    Point(const Point& other);

    // Virtual destructor
    virtual ~Point() { };

    // Getters and setters
    float GetX();
    void SetX(float x);

    float GetY();
    void SetY(float y);

    void Set(float x, float y);
    void Set(Point point);

    // Sets point coordinates given radius and angle in radians.
    void SetPolar(float r, float ang);

    // Adds two points in Cartesian coordinates.
    void Add(Point point);

    // Subtracts two points in Cartesian coordinates.
    void Subtract(Point point);

    // Multiplies point coordinates by a scalar value.
    void Multiply(float scalar);

    // Multiplies point coordinates by -1.
    void Negate();

    // Calculates the distance to another point.
    float CalculateDistance(Point point);

    // Converts to string for printing purposes.
    std::string ToString();

  protected:
    // 2-D (x, y) coordinates
    float x;
    float y;
};

#endif // POINT_H_