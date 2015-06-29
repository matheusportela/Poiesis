// Circle in 2-dimensional space.

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <string>

#include "bandit/core/math/Vector.h"

class Circle
{
  public:
    // Empty constructor.
    Circle();

    // Initialize with pre-defined (x, y) coordinates and zero radius.
    Circle(float x, float y);
    Circle(const Vector& center);

    // Initialize with pre-defined (x, y) coordinates, radius.
    Circle(float x, float y, float r);
    Circle(const Vector& center, float r);

    // Gets and sets circle's radius.
    float GetR() const;
    void SetR(float r);

    // Gets and sets circle's center.
    Vector GetCenter() const;
    void SetCenter(const Vector& center);

    // Sets circle center, radius.
    void SetCenterAndRadius(const Vector& centerVector, float r);

    // Checks whether a given vector is inside the circle's radius.
    bool IsInside(const Vector& vector) const;

    // Checks whether a given circle overlaps with this circle.
    bool Overlaps(const Circle& other) const;

    // Returns string with circle's coordinates and radius.
    std::string ToString() const;

  private:
    // 2-D (x, y) coordinates corresponding to the center.
    Vector center;

    // Circle radius.
    float r;
};

std::ostream& operator<<(std::ostream& os, const Circle& circle);

#endif // CIRCLE_H_