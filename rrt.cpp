#include "rrt.h"

RRT::RRT()
{
    statePool = {};
}

RRT::~RRT()
{
  for(vector <State*>::iterator it = statePool.begin(); it != statePool.end(); it++)
  {
      (*it)->~State();
  }
  statePool.clear();
}


void RRT::printPool()
{
  for(vector <State*>::iterator it = statePool.begin(); it != statePool.end(); it++)
  {
    (*it)->toString();
  }
}