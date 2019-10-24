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

    vector<State *> getChildren() { return children; };
    void addChild(State &childState, double dist);
    void deleteChild(State *childS){}

    State *getParent() { return parent; };
    void setParent(State *pS){parent = pS;};

    void printChildren();
    void toString();

private:
    v3d pos;
    State *parent;
    vector<State *> children;
};