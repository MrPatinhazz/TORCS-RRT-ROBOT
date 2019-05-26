#include "rrt.h"

RRT::RRT()
{
    nIter = -1;
    rootState = nullptr;
    stateVec = {};
}

RRT::~RRT()
{
    stateVec.clear;
}

