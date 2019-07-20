/**********************************************************
 *      RRT Base class. This is the class that
 *      represents the complete tree
 * 
 *********************************************************/

#pragma once

#include "state.h"

class RRT
{
    public:
        RRT(){}
        ~RRT(){}

        vector <State*> getStatePool(){return statePool;};
        void addToPool(State* newState){statePool.push_back(newState);};
        void printPool();

        //Remove state da pool

    private:
        //Pool de todos os estados criados - inclui ligados e nao ligados
        vector <State*> statePool;
};