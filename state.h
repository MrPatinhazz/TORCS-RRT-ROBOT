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
public:
    State();
    State(v3d npos);
    ~State();

    v3d getPos() { return pos; };
    void setPos(v3d pos);

    int getGraphIndex() { return graphIndex; };
    void setGraphIndex(int index) { graphIndex = index; };

    vector<State *> getChildren() { return children; };
    void addChild(State &childState)
    {
        children.emplace_back(&childState);
    };
    void printChildren();

    State getParent() { return *parent; };
    void setParent(const State &pState)
    {
        *parent = pState;
        //setGraphIndex(parent->getGraphIndex() + 1);
    };

    void toString();
    float distFromStart = 0;

private:
    v3d pos;
    int graphIndex;
    State* parent;
    vector<State *> children;
};
