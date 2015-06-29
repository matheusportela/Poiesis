// Rectangle in 2-dimensional space.

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <string>

#include "bandit/core/math/Vector.h"

class Rectangle
{
  public:
    // Empty constructor.
    Rectangle();

    // Initialize with pre-defined (x, y) coordinates and zero width and height.
    Rectangle(float x, float y);
    Rectangle(const Vector& vector);

    // Initialize with pre-defined (x, y) coordinates, width and height.
    Rectangle(float x, float y, float w, float h);
    Rectangle(const Vector& vector, float w, float h);

    // Gets and sets rectangle's dimensions.
    float GetW() const;
    void SetW(float w);
    float GetH() const;
    void SetH(float h);

    // Sets rectangle with it's center at (centerX, centerY).
    void SetCenter(const Vector& centerVector);
    Vector GetCenter() const;

    // Sets rectangle center, width and height.
    void SetCenterAndDimensions(const Vector& centerVector, float w, float h);

    // Gets and sets rectangle's extremities.
    Vector GetTopLeft() const;
    void SetTopLeft(const Vector& vector);

    Vector GetTopRight() const;
    Vector GetBottomLeft() const;
    Vector GetBottomRight() const;

    // Checks whether a given vector is inside the rectangle's dimensions.
    bool IsInside(const Vector& vector) const;

    // Checks whether a given rectangle overlaps with this rectangle.
    bool Overlaps(const Rectangle& other) const;

    // Returns string with rectangle's coordinates and dimensions.
    std::string ToString() const;

  private:
    // 2-D (x, y) coordinates corresponding to the top-left corner.
    Vector vector;

    // Rectangle width, grows from left to right.
    float w;

    // Rectangle height, grows from top to bottom.
    float h;
};

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle);

#endif // RECTANGLE_H_