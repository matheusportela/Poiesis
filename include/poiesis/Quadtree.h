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
    Quadtree(float x, float y, float width, float height, int level,
        int maxLevel, int maxObjects);
    void Add(T object, float x, float y);
    std::vector<T> Get(float x, float y);
    void Clear();

  private:
    bool IsLeaf();
    void Split();
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
    int maxObjects;
    std::vector<T> objects;
};

template <typename T>
Quadtree<T>::Quadtree(float x, float y, float width, float height, int level,
    int maxLevel, int maxObjects) :
    x(x), y(y), width(width), height(height), level(level), maxLevel(maxLevel),
    maxObjects(maxObjects)
{
}

template <typename T>
void Quadtree<T>::Add(T object, float x, float y)
{
    if (!IsLeaf())
    {
        if (Contains(nw, x, y))
            nw->Add(object, x, y);
        else if (Contains(ne, x, y))
            ne->Add(object, x, y);
        else if (Contains(sw, x, y))
            sw->Add(object, x, y);
        else if (Contains(se, x, y))
            se->Add(object, x, y);
    }
    else
    {
        objects.push_back(object);

        if (objects.size() > maxObjects && level < maxLevel)
        {
            if (IsLeaf())
                Split();

            for (T movingObject : objects)
            {
                if (Contains(nw, x, y))
                    nw->Add(movingObject, x, y);
                else if (Contains(ne, x, y))
                    ne->Add(movingObject, x, y);
                else if (Contains(sw, x, y))
                    sw->Add(movingObject, x, y);
                else if (Contains(se, x, y))
                    se->Add(movingObject, x, y);
            }

            objects.clear();
        }
    }
}

template <typename T>
bool Quadtree<T>::IsLeaf()
{
    return (!nw);
}

template <typename T>
bool Quadtree<T>::Contains(std::shared_ptr<Quadtree> child, float x, float y)
{
    return (x > child->x &&
            x <= child->x + child->width &&
            y > child->y &&
            y <= child->y + child->height);
}

template <typename T>
bool Quadtree<T>::Contains(float x, float y)
{
    return (x > this->x &&
            x <= this->x + this->width &&
            y > this->y &&
            y <= this->y + this->height);
}

template <typename T>
std::vector<T> Quadtree<T>::Get(float x, float y)
{
    if (level == maxLevel || IsLeaf())
        return objects;

    std::vector<T> returnObjects;
    
    if (x > this->x && x <= this->x + width/2)
    {
        if (y > this->y && y <= this->y + height/2)
            returnObjects = nw->Get(x, y);
        else if (y > this->y + height/2 && y <= this->y + height)
            returnObjects = sw->Get(x, y);
    }
    else if (x > this->x + width/2 && x <= this->x + width)
    {
        if (y > this->y && y <= this->y + height/2)
            returnObjects = ne->Get(x, y);
        else if (y > this->y + height/2 && y <= this->y + height)
            returnObjects = se->Get(x, y);
    }

    return returnObjects;
}

template <typename T>
void Quadtree<T>::Split()
{
    if (level != maxLevel)
    {
        float newWidth = width/2;
        float newHeight = height/2;
        int newLevel = level + 1;

        nw = std::make_shared<Quadtree>(x, y, newWidth, newHeight, newLevel, maxLevel, maxObjects);
        ne = std::make_shared<Quadtree>(x + newWidth, y, newWidth, newHeight, newLevel, maxLevel, maxObjects);
        sw = std::make_shared<Quadtree>(x, y + newHeight, newWidth, newHeight, newLevel, maxLevel, maxObjects);
        se = std::make_shared<Quadtree>(x + newWidth, y + newHeight, newWidth, newHeight, newLevel, maxLevel, maxObjects);
    }
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