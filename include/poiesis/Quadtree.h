// Quad-tree for space partitioning.
// References:
// https://github.com/veeableful/Quadtree_Minimal
// http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374

#ifndef QUAD_TREE_H_
#define QUAD_TREE_H_

#include <memory>
#include <vector>

#include "bandit/Engine.h"

template <typename T>
class Quadtree
{
  public:
    const int MAX_OBJECTS = 4;

    Quadtree(Rectangle area);
    void Add(T object, Vector position);
    std::vector<T> Get(Vector position);
    void Clear();

  private:
    bool IsLeaf();
    void Split();

    std::shared_ptr<Quadtree> nw;
    std::shared_ptr<Quadtree> ne;
    std::shared_ptr<Quadtree> sw;
    std::shared_ptr<Quadtree> se;
    Rectangle area;
    std::vector<T> objects;
    std::vector<Vector> positions;
};

template <typename T>
Quadtree<T>::Quadtree(Rectangle area) :
    area(area)
{
}

template <typename T>
void Quadtree<T>::Add(T object, Vector position)
{
    if (!area.IsInside(position))
        return;

    if (IsLeaf() && objects.size() < MAX_OBJECTS)
    {
        objects.push_back(object);
        positions.push_back(position);
    }
    else
    {
        if (IsLeaf())
            Split();

        nw->Add(object, position);
        ne->Add(object, position);
        sw->Add(object, position);
        se->Add(object, position);
    }
}

template <typename T>
bool Quadtree<T>::IsLeaf()
{
    return (!nw);
}

template <typename T>
std::vector<T> Quadtree<T>::Get(Vector position)
{
    std::vector<T> childObjects;
    std::vector<T> returnObjects;

    if (IsLeaf())
    {
        if (area.IsInside(position))
            returnObjects = objects;
    }
    else
    {
        childObjects = nw->Get(position);
        returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());

        childObjects = ne->Get(position);
        returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());

        childObjects = sw->Get(position);
        returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());

        childObjects = se->Get(position);
        returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());
    }

    return returnObjects;
}

template <typename T>
void Quadtree<T>::Split()
{
    float x = area.GetTopLeft().GetX();
    float y = area.GetTopLeft().GetY();
    float newWidth = area.GetW()/2;
    float newHeight = area.GetH()/2;
    
    nw = std::make_shared<Quadtree>(Rectangle(x, y, newWidth, newHeight));
    ne = std::make_shared<Quadtree>(Rectangle(x + newWidth, y, newWidth, newHeight));
    sw = std::make_shared<Quadtree>(Rectangle(x, y + newHeight, newWidth, newHeight));
    se = std::make_shared<Quadtree>(Rectangle(x + newWidth, y + newHeight, newWidth, newHeight));

    for (unsigned int i = 0; i < objects.size(); ++i)
    {
        nw->Add(objects[i], positions[i]);
        ne->Add(objects[i], positions[i]);
        sw->Add(objects[i], positions[i]);
        se->Add(objects[i], positions[i]);
    }

    objects.clear();
    positions.clear();
}

template <typename T>
void Quadtree<T>::Clear()
{
    if (!IsLeaf())
    {
        nw->Clear();
        ne->Clear();
        sw->Clear();
        se->Clear();
    }

    objects.clear();
}

#endif // QUAD_TREE_H_