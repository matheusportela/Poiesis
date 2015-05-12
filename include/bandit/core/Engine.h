// Run basic engine initialization and shutdown methods.
//
// Some modules must be initialized in order to provide functionality to the
// higher-level modules. Also, they must be properly shutdown, avoiding memory
// leaks and system crashing.

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>

class Engine
{
  public:
    Engine();
    ~Engine();
};

#endif // ENGINE_H_