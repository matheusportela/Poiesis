// @file   CollisionSimulator.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Simulates collision detection and reaction between game objects.

#include "CollisionSimulator.h"

void CollisionSimulator::Collide()
{
    std::shared_ptr<GameObject> object1;
    std::shared_ptr<GameObject> object2;

    for (int i = 0; i < GameObjectManager::GetInstance().GetSize()-1; ++i)
    {
        for (int j = i+1; j < GameObjectManager::GetInstance().GetSize(); ++j)
        {
            object1 = GameObjectManager::GetInstance().GetObject(i);
            object2 = GameObjectManager::GetInstance().GetObject(j);

            if (IsColliding(object1, object2))
            {
                object1->NotifyCollision(object2);
                object2->NotifyCollision(object1);
            }
        }
    }
}

bool CollisionSimulator::IsColliding(std::shared_ptr<GameObject> object1,
    std::shared_ptr<GameObject> object2)
{
    Point p1 = object1->GetPoint();
    Rect r1 = object1->GetBox();
    Point p2 = object2->GetPoint();
    Rect r2 = object2->GetBox();

    Point A[] =
    {
        Point(p1.GetX(), p1.GetY() + r1.GetH()),
        Point(p1.GetX() + r1.GetW(), p1.GetY() + r1.GetH()),
        Point(p1.GetX() + r1.GetW(), p1.GetY()),
        Point(p1.GetX(), p1.GetY())
    };

    Point B[] =
    {
        Point(p2.GetX(), p2.GetY() + r2.GetH()),
        Point(p2.GetX() + r2.GetW(), p2.GetY() + r2.GetH()),
        Point(p2.GetX() + r2.GetW(), p2.GetY()),
        Point(p2.GetX(), p2.GetY())
    };

    for (auto& v : A) {
        v = Rotate(v - object1->GetCenter(), object1->GetRotation()) + object1->GetCenter();
    }

    for (auto& v : B) {
        v = Rotate(v - object2->GetCenter(), object2->GetRotation()) + object2->GetCenter();
    }

    Point axes[] =
    {
        Norm(A[0] - A[1]),
        Norm(A[1] - A[2]),
        Norm(B[0] - B[1]),
        Norm(B[1] - B[2])
    };

    for (auto& axis : axes)
    {
        float P[4];

        for (int i = 0; i < 4; ++i)
            P[i] = Dot(A[i], axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i)
            P[i] = Dot(B[i], axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

float CollisionSimulator::Mag(const Point& p)
{
    return std::sqrt(p.GetX()*p.GetX() + p.GetY()*p.GetY());
}

Point CollisionSimulator::Norm(const Point& p)
{
    return p*(1.f/Mag(p));
}

float CollisionSimulator::Dot(const Point& a, const Point& b)
{
    return a.GetX()*b.GetX() + a.GetY()*b.GetY();
}

Point CollisionSimulator::Rotate(const Point& p, float angle)
{
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    return Point(p.GetX()*cs - p.GetY()*sn, p.GetX()*sn + p.GetY()*cs);
}