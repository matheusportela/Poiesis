// Vector in 2-dimensional space, to represente position, velocity or
// acceleration, for instance.

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>
#include <string>

#include "bandit/core/Log.h"

class Vector
{
  public:
    // Empty constructor.
    Vector();

    // Initializes with pre-defined x and y values.
    Vector(float x, float y);

    // Copy constructor.
    Vector(const Vector& other);

    // Compound assignment operators.
    Vector& operator+=(const Vector &rhs);
    Vector& operator-=(const Vector &rhs);
    Vector& operator*=(const Vector &rhs);
    Vector& operator/=(const Vector &rhs);

    // Binary arithmetic operators.
    const Vector operator+(const Vector &rhs) const;
    const Vector operator-(const Vector &rhs) const;
    const Vector operator*(const Vector &rhs) const;
    const Vector operator/(const Vector &rhs) const;

    // Comparison operators.
    bool operator==(const Vector &rhs) const;
    bool operator!=(const Vector &rhs) const;

    // Getters and setters
    float GetX() const;
    void SetX(float x);

    float GetY() const;
    void SetY(float y);

    // Calculates the magnitude, also known as norm or absolute value.
    float GetMagnitude() const;

    // Calculates the direction (in radians).
    float GetDirection() const;

    void Set(float x, float y);
    void Set(Vector vector);

    // Sets vector coordinates given magnitude and direction (in radians).
    void SetPolar(float magnitude, float direction);

    // Adds two vectors in Cartesian coordinates.
    void Add(Vector vector);

    // Subtracts two vectors in Cartesian coordinates.
    void Subtract(Vector vector);

    // Multiplies vector coordinates by a scalar value.
    void Multiply(float scalar);

    // Divides vector coordinates by a scalar value, except zero.
    void Divide(float scalar);

    // Multiplies vector coordinates by -1.
    void Negate();

    // Rotates vector by an angle (in radians) couterclockwise.
    void Rotate(float angle);

    // Adjusts the x, y coordinates such that the vector norm is 1.
    void Normalize();

    // Limits vector magnitude to the maximum given value.
    void Saturate(float maximum);

    // Calculates the distance to another vector.
    float CalculateDistance(Vector vector) const;

    // Converts to string for printing purposes.
    std::string ToString() const;

  protected:
    // 2-D (x, y) coordinates
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& os, const Vector& vector);

#endif // VECTOR_H_