// Interface to system initialization and shutdown procedures.

#ifndef SYSTEM_ADAPTER_H_
#define SYSTEM_ADAPTER_H_

class SystemAdapter
{
  public:
    virtual ~SystemAdapter() {}
    
    // Deals with subsystems initialization.
    virtual void Initialize() = 0;

    // Deals with subsystems shutdown.
    virtual void Shutdown() = 0;
};

#endif // SYSTEM_ADAPTER_H_