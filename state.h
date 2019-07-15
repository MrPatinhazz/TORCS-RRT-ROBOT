/**********************************************************
 *          State/Tree node class. Represents each
 *          node of the tree
 * 
 * ********************************************************/

#pragma once

#include "car.h"
#include <vector>
#include <iostream>
#include <string>
#include "linalg.h"

using namespace std;

class State
{
    private:
        v3d pos;
        int graphIndex;
        State* parent;
        vector <State*> children;

    public:
        State();
        State(v3d pos);
        ~State();

        v3d getPos(){return pos;};
        void setPos(v3d pos);

        int getGraphIndex(){return graphIndex;};
        void setGraphIndex(int index);

        void toString();
        float distFromStart = 0;
};

