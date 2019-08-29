/**********************************************************
 *      RRT Base class. This is the class that
 *      represents the complete tree
 * 
 *********************************************************/

#pragma once

#include "state.h"
#include "heuristics.h"

using namespace std;

class RRT
{
public:
    RRT();
    ~RRT();

    vector<State *> getPool() { return statePool; };
    void addToPool(State &newState) { statePool.emplace_back(&newState); };
    void addState(State *nearState, v3d *pos);
    State *getAt(int index) { return statePool.at(index); };

    State *getRoot() { return statePool.front(); };

    void printPool();
    void printTree();

private:
    //Pool de todos os estados criados - inclui ligados e nao ligados
    vector<State *> statePool;
};