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
    statePool.at(k)->~State();
  }
  statePool.clear();
}

void RRT::addNewStep()
{
    cout << "test" << endl;
    return;
}

void RRT::printPool()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool.at(k)->toString();
  }
}