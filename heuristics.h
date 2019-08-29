/** 
 * Support functions and RRT heuristics
*/

#pragma once

#include "berniw.h"

using namespace std;

const double _stepsize = 10;

//Random number/state generators
class RandomGen
{
public:
	//Random number within fMin-fMax
	inline static double fRands(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

	//Generates a random state using the complete track area
	static v3d CTAPos(tTrack *myTrack, TrackDesc *myTrackDesc)
	{
		double randx = fRands(myTrack->min.x, myTrack->max.x);
		double randy = fRands(myTrack->min.y, myTrack->max.y);
		double maxz = myTrack->max.z;
		return v3d(randx, randy, maxz);
	}
};

class Dist
{
public:
	static double inline eucl(v3d a, v3d b)
	{
		return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
	}
};

class Trig
{
public:
	static double angleBetween(v3d *a, v3d *b)
	{
		return atan2(b->x - a->x, b->y - a->y) * 180 / PI;
	};
};

class Util
{
public:
	static v3d step(v3d *nearState, v3d *randPos)
	{
		double angle = Trig::angleBetween(nearState, randPos);
		double nx = nearState->x + (_stepsize * sin(DEG2RAD(angle)));
		double ny = nearState->y + (_stepsize * cos(DEG2RAD(angle)));
		return v3d(nx, ny, nearState->z);
	};

	static bool isPosValid(tTrack *myTrack, TrackDesc *myTrackDesc, v3d *pos)
	{
		int closestid = myTrackDesc->getNearestId(pos);
		double distToPos = myTrackDesc->getSegmentPtr(closestid)->distToMiddle2D(pos->x, pos->y);
		double distToBorder = distToPos - myTrack->width;
		//< 0 - 2 to account for track margin
		return (distToBorder < -7);
	};
};