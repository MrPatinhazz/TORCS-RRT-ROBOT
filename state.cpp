#include "state.h"

State::State()
{
  pos = v3d(0, 0, 0);
  graphIndex = 0;
  parent = nullptr;
  children = {};
  edgeCost = 0;
}

State::State(v3d npos)
{
  pos = npos;
  graphIndex = 0;
  parent = nullptr;
  children = {};
  edgeCost = 0;
}

State::~State()
{
}

void State::toString()
{
  cout << "X:" << pos.x;
  cout << " Y:" << pos.y;
  cout << " Z:" << pos.z << endl;
}

void State::printChildren()
{
  for (size_t k = children.size(); k--;)
  {
    cout << children[k] << " ";
  }
}

void State::addChild(State &childState, double dist)
{
  children.emplace_back(&childState);
  childState.parent = &(*this);
  childState.graphIndex = childState.parent->graphIndex + 1;
  childState.edgeCost = childState.parent->edgeCost + dist;
}