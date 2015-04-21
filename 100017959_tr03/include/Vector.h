// @file   Vector.h
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Vector in 2-dimensional space

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

#include "Logger.h"
#include "Point.h"

class Vector : public Point
{
  public:
    // Calculates the magnitude, also known as norm or absolute vector.
    float GetMagnitude();

    // Calculates the direction (in radians).
    float GetDirection();

    // Rotates vector by an angle (in radians) couterclockwise.
    void Rotate(float angle);

    // Adjusts the x, y coordinates such that the vector norm is 1.
    void Normalize();
};

#endif // VECTOR_H_