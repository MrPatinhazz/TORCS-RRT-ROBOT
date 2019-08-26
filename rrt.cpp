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

void RRT::printPool()
{
  for (size_t k = 0; k < statePool.size(); k++)
  {
    statePool.at(k)->toString();
  }
}

void RRT::addNewStep(State* minDistState, v3d &randPos)
{
    cout << "test" << endl;
  	double angle = Trig::angleBetween(minDistState->getPos(), &randPos);
		v3d newStep = Util::step(minDistState->getPos(),angle);
		State *newState = new State(newStep);
		(*newState);
		minDistState->addChild(*newState);
}