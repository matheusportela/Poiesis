// @file   ActionScheduler.cpp
// @author Matheus Vieira Portela
// @date   27/04/2015
//
// @brief Schedule actions to execute sequentially.

#include "ActionScheduler.h"

void ActionScheduler::Schedule(std::shared_ptr<Action> action)
{
    LOG_D("[ActionScheduler] Scheduling action");

    queue.push(action);
}

void ActionScheduler::Execute()
{
    bool finished = false;

    // Selecting new action
    if (!executingAction and queue.size() > 0)
    {
        executingAction = queue.front();
        executingAction->PreExecute();
    }

    // Executing action
    if (executingAction)
    {
        executingAction->Execute();
        finished = executingAction->IsFinished();
    }

    // Finishing action
    if (finished)
    {
        LOG_D("[ActionScheduler] Action finished");
        executingAction->PostExecute();
        executingAction.reset();
        queue.pop();
    }
}