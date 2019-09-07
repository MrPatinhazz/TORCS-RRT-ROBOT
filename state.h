/**********************************************************
 *          State/Tree node class. Represents each
 *          node of the tree
 * 
 * ********************************************************/

#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "linalg.h"
#include "car.h"

using namespace std;

class State
{
public:
    State();
    State(v3d npos);
    ~State();

    v3d *getPos() { return &pos; };
    void setPos(v3d pos);

    int getGraphIndex() { return graphIndex; };
    void setGraphIndex(int index) { graphIndex = index; };

    vector<State *> getChildren() { return children; };
    void addChild(State &childState)
    {
        children.emplace_back(&childState);
        childState.parent = &(*this);
        childState.graphIndex = childState.parent->graphIndex + 1;
    };
    State *getParent() { return parent; };

    void printChildren();
    void toString();
    float distFromStart = 0;

private:
    v3d pos;
    int graphIndex;
    State *parent;
    vector<State *> children;
};