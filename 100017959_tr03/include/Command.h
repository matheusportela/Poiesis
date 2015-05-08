// @file   Command.h
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Manager for user input

#ifndef COMMAND_H_
#define COMMAND_H_

class Command
{
  public:
    virtual void Execute() = 0;
};

#endif // COMMAND_H_