// Components are inserted inside entities to provide some capabilities that
// will be processed by systems.
//
// Components are, in fact, only a container class that stores attributes.

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

class Component
{
  public:
    virtual ~Component() {}

    // Allows components to be identified.
    virtual std::string GetComponentClass() = 0;
};

#endif // COMPONENT_H_