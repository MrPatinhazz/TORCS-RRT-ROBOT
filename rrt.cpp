#include "rrt.h"

void RRT::printPool()
{
  for(vector<State*>::iterator it = statePool.begin(); it != statePool.end(); it++)
  {
      cout<< *it << endl;
  }
}