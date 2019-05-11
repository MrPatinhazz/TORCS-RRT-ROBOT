/**********************************************************
 *          State/Tree node class. Represents each
 *          node of the tree
 * 
 * ********************************************************/

#pragma once

#include "car.h"
#include <iostream>
#include <string>

class State
{
    private:
        tPosd pos;

        int graphIndex;
        int parentGIndex;


    public:
    float distFromStart = 0;
        State();
        State(tPosd pos);

        tPosd getPos();
        void setPos(tPosd pos);

        int getGraphIndex();
        void setGraphIndex(int index);

        int getParentGIndex();
        void setParentGIndex(int index);

        std::string toString();

};

