/** 
 * Support functions and RRT heuristics
*/

#pragma once

#include "berniw.h"

//Random number/state generators
class RandomGen
{
public:

	//Random number withing fMin-fMax
	inline static double fRands(double fMin, double fMax)
	{
    	double f = (double)rand() / RAND_MAX;
    	return fMin + f * (fMax - fMin);
	}

	// Generates random state inside track
	static v3d ITPos(tTrack *myTrack, TrackDesc *myTrackDesc)
	{
		double randx = fRands(myTrack->min.x, myTrack->max.x);
		double randy = fRands(myTrack->min.y, myTrack->max.y);
		double maxz = myTrack->max.z;
		v3d randpos = v3d(randx, randy, maxz);

		int closestid = myTrackDesc->getNearestId(&randpos);
		double distToPos = myTrackDesc->getSegmentPtr(closestid)->distToMiddle2D(randpos.x, randpos.y);
		double distToBorder = distToPos - myTrack->width;
		cout << "To border: " << distToBorder << endl;
		//< 0 - 2 to account for track margin
		if (distToBorder < -2)
		{
			return randpos;
		}
		else
		{
			return v3d(0, 0, 0);
		}
	};

	//Generates a random state using the complete track area
	static v3d CTAPos(tTrack *myTrack, TrackDesc *myTrackDesc)
	{
		double randx = fRands(myTrack->min.x, myTrack->max.x);
		double randy = fRands(myTrack->min.y, myTrack->max.y);
		double maxz = myTrack->max.z;
		v3d randpos = v3d(randx, randy, maxz);
		return randpos;
	}
};

class Dist
{
public:
	static double inline eucl(v3d a, v3d b)
	{
		return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
	}
};