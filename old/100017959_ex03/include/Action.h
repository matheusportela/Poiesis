// @file   Action.h
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Action interface as Command design pattern.
//
// Action provides a single interface that allows a loose coupling between
// reusable game object actions and it's owners.
// It's inspired by the Command design pattern, explained in details at this
// link: http://gameprogrammingpatterns.com/command.html

#ifndef ACTION_H_
#define ACTION_H_

#include "GameObject.h"

class Action
{
  public:
    Action(GameObject* object) : attachedObject(object) {};

    virtual ~Action() {};

    // Executes once before the action execution.
    virtual void PreExecute() {}

    // Executes the action. This method is called every game loop while the
    // action has not finished.
    virtual void Execute() = 0;

    // Executes once after the action execution.
    virtual void PostExecute() {}

    // Checks whether the action has finished.
    virtual bool IsFinished() = 0;

  protected:
    // Game object that executes the action.
    GameObject* attachedObject;
};

#endif // ACTION_H_