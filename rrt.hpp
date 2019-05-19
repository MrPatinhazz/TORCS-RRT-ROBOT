/**********************************************************
 *      RRT Base class. This is the class that
 *      represents the complete tree
 * 
 *********************************************************/

#pragma once

#include "state.hpp"
#include <vector>

class RRT
{
    private:
        int nIter;
        State* rootState;

    public:
        RRT(State rootState){}
        ~RRT(){}
};