#include "state.h"

State::State()
{
    pos = v3d(0,0,0);
    graphIndex = 0;
    parent = nullptr;
    children = {};
}

State::State(v3d npos)
{
    pos = npos;
    graphIndex = 0;
    parent = nullptr;
    children = {};
}

State::~State()
{
}

void State::toString()
{
    cout<< "Current Pos :" << endl;
    cout << "X:"  << pos.x;
    cout << " Y:" << pos.y;
    cout << " Z:" << pos.z << endl;
}