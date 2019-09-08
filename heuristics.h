/** 
 * Support functions and RRT heuristics
*/

#pragma once

#include "berniw.h"

using namespace std;

const double _stepsize = 7;

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

	static bool isPosValid(tTrack *myTrack, TrackDesc *myTrackDesc, v3d *pos, OtherCar* ocar)
	{
		int closestid = myTrackDesc->getNearestId(pos);
		double distToPos = myTrackDesc->getSegmentPtr(closestid)->distToMiddle2D(pos->x, pos->y);
		double distToBorder = distToPos - myTrack->width;

		//< 0 - 2 to account for track margin
		return distToBorder < -7 && isInside(0 , myTrack->max.x, 0, myTrack->max.y,pos->x, pos->y) ;		
	};

	static bool isInside(double x1, double x2, double y1, double y2, double xa, double ya)
	{
		return isBetween(x1,x2,xa) && isBetween(y1,y2,ya);
	}

	static bool isBetween(double p1, double p2, double a)
	{
		if(p1 >= p2 && a < p1 && a > p2 )
		{
			return true;
		}
		else if(p1 <= p2 && a < p2 && a > p1)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
};