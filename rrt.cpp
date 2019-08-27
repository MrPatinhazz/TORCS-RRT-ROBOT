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

void RRT::addNewStep(State *nearState, v3d *randPos)
{
    double angle = Trig::angleBetween(nearState->getPos(), randPos);
		v3d newStep = Util::step(nearState->getPos(),angle);
		State *newState = new State(newStep);
		addToPool(*newState);
		nearState->addChild(*newState);
}

void RRT::printPool()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool.at(k)->toString();
  }
}