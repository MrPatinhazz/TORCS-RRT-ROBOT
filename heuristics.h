/** 
 * Support functions and RRT heuristics & parameters
*/

#pragma once

#include "berniw.h"

using namespace std;

//RRT Parameters
#define DRAWWIN 1	  // Draws window
#define MAKEPATH 1	 // Makes path
#define SEGMARGIN 4.5  // Security margin (measured from mid segment)
#define STEPSIZE 10  // Branch (step) size - Recommended < 0.50
#define TREESIZE 25000 // Tree Size - Recomended > 16k
#define ITERGROWTH 1  // If tree grows iteratively (1) or completly offline (0)
#define EXPFREQ 1	 // The tree expands each EXPFREQ frames (if ITERGROWTH)
#define NBR_RADIUS 2   // Neighboorhood (close states) radius
#define ANGLELIMIT 155 // AB^C > ANGLELIMIT - A->B parent, B->xNear, C->xNew 

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

	// a is xNear, b is xNew, c is parent of a
	static double branchAngle(v3d *a, v3d *b, v3d *c)
	{
		double AB = Dist::eucl(*a, *b);
		double AC = Dist::eucl(*a, *c);
		double BC = Dist::eucl(*b, *c);

		return RAD2DEG(acos(((AB*AB) + (AC*AC) - (BC*BC)) / (2 * AB * AC)));
	};
};

class Util
{
public:
	static v3d step(v3d *nearState, v3d *randPos)
	{
		double angle = Trig::angleBetween(nearState, randPos);
		double nx = nearState->x + (STEPSIZE * sin(DEG2RAD(angle)));
		double ny = nearState->y + (STEPSIZE * cos(DEG2RAD(angle)));
		return v3d(nx, ny, nearState->z);
	};

	static bool isPosValid(tTrack *myTrack, TrackDesc *myTrackDesc, v3d *pos, OtherCar *ocar)
	{
		//Ignores validation
		//return true;
		int closestid = myTrackDesc->getNearestId(pos);
		double distToPos = myTrackDesc->getSegmentPtr(closestid)->distToMiddle2D(pos->x, pos->y);
		//return  //&& isInside(0 , myTrack->max.x, 0, myTrack->max.y,pos->x, pos->y) ;
		return (distToPos < SEGMARGIN);
	};

	static bool isInside(double x1, double x2, double y1, double y2, double xa, double ya)
	{
		return isBetween(x1, x2, xa) && isBetween(y1, y2, ya);
	}

	static bool isBetween(double p1, double p2, double a)
	{
		if (p1 >= p2 && a < p1 && a > p2)
		{
			return true;
		}
		else if (p1 <= p2 && a < p2 && a > p1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static int findMinIndex(v3d pos, vector<State *> list)
	{
		int minIndex = -1;
		double minStDist = 9999;
		double dist = -1;

		for (size_t k = list.size(); k--;)
		{
			dist = Dist::eucl(pos, *list.at(k)->getPos());

			if (dist > 0 && dist < minStDist)
			{
				minStDist = dist;
				minIndex = k;
			}
		}
		return minIndex;
	}
};
