#include "state.h"

State::State()
{
    pos = v3d(0,0,0);
    graphIndex = -1;
    parentGIndex = -1;
    distFromStart = -1;
}

State::State(v3d *tpos)
{
    pos = *tpos;
    graphIndex = -1;
    parentGIndex = -1;
    distFromStart = -1;
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