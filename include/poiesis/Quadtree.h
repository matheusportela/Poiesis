// Quad-tree for space partitioning.
// Base code at https://github.com/veeableful/Quadtree_Minimal

#ifndef QUAD_TREE_H_
#define QUAD_TREE_H_

#include <memory>
#include <vector>

#include "bandit/Engine.h"

template <typename T>
class Quadtree
{
  public:
    Quadtree(float x, float y, float width, float height, int level,
        int maxLevel);
    void Add(T object, float x, float y);
    std::vector<T> Get(float x, float y);
    void Clear();

  private:
    bool Contains(std::shared_ptr<Quadtree> child, float x, float y);
    bool Contains(float x, float y);

    std::shared_ptr<Quadtree> nw;
    std::shared_ptr<Quadtree> ne;
    std::shared_ptr<Quadtree> sw;
    std::shared_ptr<Quadtree> se;
    float x;
    float y;
    float width;
    float height;
    int level;
    int maxLevel;
    std::vector<T> objects;
};

template <typename T>
Quadtree<T>::Quadtree(float x, float y, float width, float height, int level,
    int maxLevel) :
    x(x), y(y), width(width), height(height), level(level), maxLevel(maxLevel)
{
    if (level != maxLevel)
    {
        nw = std::make_shared<Quadtree>(x, y, width/2, height/2, level + 1, maxLevel);
        ne = std::make_shared<Quadtree>(x + width/2, y, width/2, height/2, level + 1, maxLevel);
        sw = std::make_shared<Quadtree>(x, y + height/2, width/2, height/2, level + 1, maxLevel);
        se = std::make_shared<Quadtree>(x + width/2, y + height/2, width/2, height/2, level + 1, maxLevel);
    }
}

template <typename T>
void Quadtree<T>::Add(T object, float x, float y)
{
    if (level == maxLevel)
    {
        objects.push_back(object);
    }
    else
    {
        if (Contains(nw, x, y))
        {
            nw->Add(object, x, y);
            return;
        }
        else if (Contains(ne, x, y))
        {
            ne->Add(object, x, y);
            return;
        }
        else if (Contains(sw, x, y))
        {
            sw->Add(object, x, y);
            return;
        }
        else if (Contains(se, x, y))
        {
            se->Add(object, x, y);
            return;
        }
        
        if (Contains(x, y))
            objects.push_back(object);
    }
}

template <typename T>
bool Quadtree<T>::Contains(std::shared_ptr<Quadtree> child, float x, float y)
{
    return !(x < child->x ||
             y < child->y ||
             x > child->x + child->width  ||
             y > child->y + child->height);
}

template <typename T>
bool Quadtree<T>::Contains(float x, float y)
{
    return !(x < x ||
             y < y ||
             x > x + width  ||
             y > y + height);
}

template <typename T>
std::vector<T> Quadtree<T>::Get(float x, float y)
{
    if (level == maxLevel)
        return objects;

    std::vector<T> returnObjects;
    std::vector<T> childObjects;

    if (!objects.empty())
        returnObjects = objects;

    if (x > this->x + width/2 && x < this->x + width)
    {
        if (y > this->y + height/2 && y < this->y + height)
        {
            childObjects = se->Get(x, y);
            returnObjects.insert(returnObjects.end(), childObjects.begin(),
                childObjects.end());
        }
        else if (y > this->y && y <= this->y + height/2)
        {
            childObjects = ne->Get(x, y);
            returnObjects.insert(returnObjects.end(), childObjects.begin(),
                childObjects.end());
        }
    }
    else if (x > this->x && x <= this->x + width/2)
    {
        if (y > this->y + height/2 && y < this->y + height)
        {
            childObjects = sw->Get(x, y);
            returnObjects.insert(returnObjects.end(), childObjects.begin(),
                childObjects.end());
        }
        else if (y > this->y && y <= this->y + height/2)
        {
            childObjects = nw->Get(x, y);
            returnObjects.insert(returnObjects.end(), childObjects.begin(),
                childObjects.end());
        }
    }

    return returnObjects;
}

template <typename T>
void Quadtree<T>::Clear()
{
    if (nw)
        nw->Clear();

    if (ne)
        ne->Clear();

    if (sw)
        sw->Clear();

    if (se)
        se->Clear();

    objects.clear();
}

#endif // QUAD_TREE_H_