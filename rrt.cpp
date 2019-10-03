#include "rrt.h"

double _angle = 0;

RRT::RRT()
{
  statePool = {};
}

RRT::~RRT()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool[k]->~State();
  }
  statePool.clear();
}

void RRT::addState(State *nearState, v3d *pos, double dist)
{
  State *newState = new State(*pos);
  addToPool(*newState);
  nearState->addChild(*newState, dist);
}

void RRT::printPool()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool.at(k)->toString();
  }
}

void RRT::backtrack()
{
  if(!pathVec.empty())
  {
    State* currState = pathVec.back();
    while(currState->getParent() != nullptr)
    {
      pathVec.emplace_back(currState->getParent());
      currState = currState->getParent();
    }
  }
  else
  {
    cout << "Path vector empty, impossible to backtrack" << endl;
  }  
}