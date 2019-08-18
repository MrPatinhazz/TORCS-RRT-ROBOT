#include "rrt.h"

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

void RRT::printPool()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool.at(k)->toString();
  }
}