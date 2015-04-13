// @file   Vector.h
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Vector in 2-dimensional space

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>
#include <string>

#include "Point.h"

class Vector
{
  public:
    // Empty constructor.
    Vector();

    // Initialize with pre-defined (x, y) coordinates.
    Vector(float x, float y);

    // Copy constructor.
    Vector(Vector& other);

    // Getters and setters
    float GetX();
    void SetX(float x);

    float GetY();
    void SetY(float y);

    void Set(float x, float y);

    // Set vector coordinates given a magnitude and direction (in radians).
    void SetPolar(float magnitude, float direction);

    // Calculates the magnitude, also known as norm or absolute vector.
    float GetMagnitude();

    // Calculates the direction (in radians).
    float GetDirection();

    // Adds two Euclidean vectors.
    void Add(Vector& vector);

    // Subtracts two Euclidean vectors.
    void Subtract(Vector& vector);

    // Multiplies vector by a scalar.
    void Multiply(float scalar);

    // Rotates vector by an angle (in radians) couterclockwise.
    void Rotate(float angle);

    // Adjusts the x, y coordinates such that the vector norm is 1.
    void Normalize();

    // Converts to string for printing purposes.
    std::string ToString();

    // Converts vector to point with x, y coordinates.
    Point ToPoint();

  private:
    // 2-D (x, y) coordinates
    float x;
    float y;
};

#endif // VECTOR_H_