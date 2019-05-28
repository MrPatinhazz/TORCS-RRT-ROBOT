/**********************************************************
 *      RRT Base class. This is the class that
 *      represents the complete tree
 * 
 *********************************************************/

#pragma once

#include "state.h"
#include <vector>

class RRT
{
    public:
        RRT(){}
        ~RRT(){}

        State* getRoot(){return rootState;};
        void setRoot(State *_st){rootState = _st;};

        //Unnecessary after the search() method is implemented
        vector<State> getSVec(){return stateVec;};
        void addState(State st){stateVec.push_back(st);};

        int getIter(){return nIter;};
        void incrIter(){nIter++;};

    private:
        int nIter;
        State* rootState;
        vector<State> stateVec;
};