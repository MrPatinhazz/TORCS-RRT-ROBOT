#include "dwindow.h"

//DRAW TRIGGERS
#define DRAWMAPWIN 1   // Map window
#define DRAWSTATSWIN 0 // Stats window
#define DRAWPLAN 1	 // K1999 plan
#define DRAWMAP 1	  // Map segments
#define DRAWPOS 0	  // Car(s) position
#define DRAWPATH 0	 // RRT init-goal path
#define DRAWRRT 0	  // RRT full tree

//DRAW PARAMS
#define MAPSEGWIDTH 1
#define CIRCLEWIDTH 3
#define LINEWIDTH 0.5
#define SCALE 1.5
#define STEPSKIP 1
#define LOOKBACKDIST 40
#define LOOKAHEADDIST 40

//GLCOLORS
#define WHITE 1, 1, 1
#define BLACK 0, 0, 0
#define DKGREY 0.5,0.5,0.5
#define LGTGREY 0.92, 0.92, 0.92
#define RED 1, 0, 0
#define ORANGE 1, 0.6, 0.0
#define PURPLE 1, 0.16, 0.95
#define BLUE 0, 0, 1
#define GREEN 0, 0.760, 0
#define YELLOW 1, 1, 0

//GLOBAL SUP VARS
string infoString;
MyCar *dwCar;
RRT *dwRRT;
TrackDesc *dwTrDesc;
Pathfinder *dwPf;
OtherCar *dwOcar;
Situation *dwSit;
int nTSeg = 0;
const GLfloat twicePi = PI * 2.0f;
int currSeg = 0;

DWindow::DWindow(int w, int h, MyCar *mcar, RRT *mrrt, TrackDesc *mtdesc, Pathfinder *mpf, OtherCar *mOcar, Situation *mSit)
{
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_CONTINUE_EXECUTION);

	dwCar = mcar;
	dwRRT = mrrt;
	dwTrDesc = mtdesc;
	dwPf = mpf;
	dwOcar = mOcar;
	dwSit = mSit;

	if (DRAWSTATSWIN)
	{
		glutInitWindowSize(300, 300);
		statsInt = glutCreateWindow("Stats");
		glutPositionWindow(250, 0);
		glutDisplayFunc(drawStatsWindow);
	}

	if (DRAWMAPWIN)
	{
		glutInitWindowSize(w * SCALE, h * SCALE);
		pathInt = glutCreateWindow("Drawing path");
		glutPositionWindow(420, 0);
		glutDisplayFunc(drawPathWindow);
	}
}

void DWindow::setRRT(RRT *mrrt)
{
	dwRRT = nullptr;
	dwRRT = mrrt;
}

DWindow::~DWindow()
{
	glutDestroyWindow(statsInt);
	glutDestroyWindow(pathInt);
}

void DWindow::Redisplay()
{

	int gameplayWindow = glutGetWindow();

	if (DRAWSTATSWIN)
	{
		infoString = getInfoS();
		glutSetWindow(statsInt);
		glutPostRedisplay();
	}

	if (DRAWMAPWIN)
	{
		glutSetWindow(pathInt);
		glutPostRedisplay();
	}

	glutSetWindow(gameplayWindow);
}

// STATS WINDOWS FUNCTIONS
void drawStatsWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(WHITE, 1);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glColor3f(BLACK);
	printText(10, 30, (char *)infoString.c_str());

	glPopMatrix();
	glutSwapBuffers();
}

void printText(int x, int y, char *string)
{
	int length, i;
	length = strlen(string);
	glRasterPos2i(x, y); //find where to start printing (pixel information)
	for (i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]); // Print a character of the text on the window
	}
}

// PATH WINDOWS FUNCTIONS
void drawPathWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(LGTGREY, 1);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	//Draw map segments
	if (DRAWMAP)
	{
		glColor3f(DKGREY);
		drawMapSegments();
	}

	//Draw Plan
	if (DRAWPLAN)
	{
		glColor3f(PURPLE);
		drawPlan();
	}

	//Draws all cars current position
	if (DRAWPOS)
	{
		drawPos();
	}

	//Draws states position and connections
	if (DRAWRRT)
	{
		drawRRT();
	}

	//Draws RRT Path
	if (DRAWPATH)
	{
		drawPath();
	}

	glPopMatrix();
	glutSwapBuffers();
}

void drawMapSegments()
{
	for (int i = 0; i <= dwTrDesc->getnTrackSegments(); i = i + STEPSKIP)
	{
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getLeftBorder(), MAPSEGWIDTH);
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getRightBorder(), MAPSEGWIDTH);
	}
}

void drawPlan()
{
	for (int i = 0; i <= dwPf->getnPathSeg(); i = i + STEPSKIP)
	{
		drawCircleP(dwPf->getPathSeg(i)->getOptLoc(), 0.8);
	}
	glColor3f(GREEN);

	for (int i = 0; i <= dwPf->getnPathSeg(); i = i + STEPSKIP)
	{
		drawCircleP(dwPf->getPathSeg(i)->getLoc(), 0.8);
	}
};

void drawRRT()
{
	vector<State *> dwPool = dwRRT->getPool();
	if (!dwPool.empty())
	{
		for (size_t j = dwPool.size(); j--;)
		{
			/*
			glColor3f(BLUE);
			drawCircleP(dwPool[j]->getPos(), 2);
			*/

			//Draws trees connections (edges)
			glColor3f(BLACK);
			vector<State *> sChildren = dwPool[j]->getChildren();
			if (!sChildren.empty())
			{
				for (size_t k = sChildren.size(); k--;)
				{
					drawLine(dwPool[j], sChildren[k]);
				}
			}
		}
	}
}

void drawPath()
{
	vector<State *> dwPath = dwRRT->getPathV();
	if (!dwPath.empty())
	{
		for (size_t j = dwPath.size(); j--;)
		{
			glColor3f(BLUE);
			drawCircleP(dwPath[j]->getPos(), 0.8);
		}
		glColor3f(YELLOW);
		drawCircleP(dwPath[dwPath.size() - 1]->getPos(), 1);
	}
}

void drawCorners(tCarElt *car)
{
	for (int c = 4; c--;)
	{
		drawCircle(car->pub.corner[c], 1.5);
	}
}

void drawPos()
{
	nTSeg = dwTrDesc->getnTrackSegments();

	for (int j = dwSit->raceInfo.ncars; j--;)
	{
		currSeg = dwOcar[j].getCurrentSegId();

		glColor3f(ORANGE);
		drawCircleP(dwOcar[j].getCurrentPos(), 2);

		glColor3f(BLUE);
		drawCorners(dwOcar[j].getCarPtr());

		glColor3f(YELLOW);
		int lookBackIndex = currSeg - LOOKBACKDIST;
		if (lookBackIndex < 0)
		{
			// nSeg - (LBR - CurrSeg). ex 300 - (40-39) = 299
			lookBackIndex = nTSeg - (LOOKBACKDIST - currSeg);
		}
		v3d *backpos = dwTrDesc->getSegmentPtr(lookBackIndex)->getMiddle();
		drawCircleP(backpos, 2);

		int lookAheadIndex = currSeg + LOOKAHEADDIST;
		if (lookAheadIndex >= nTSeg)
		{
			// ex (300 + 40) - 300 = 40
			lookAheadIndex -= nTSeg;
		}
		v3d *frontpos = dwTrDesc->getSegmentPtr(lookAheadIndex)->getMiddle();
		drawCircleP(frontpos, 2);
	}

	//Draws own car current position
	glColor3f(RED);
	drawCircleP(dwCar->getCurrentPos(), 2);
}

void drawCircle(tPosd point, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (point.ax * SCALE);
	int y = h - (point.ay * SCALE);

	int i;
	int triangleAmount = 30;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(CIRCLEWIDTH);

	glBegin(GL_LINES);
	for (i = triangleAmount; i--;)
	{
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

void drawCircleP(v3d *pos, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (pos->x * SCALE);
	int y = h - (pos->y * SCALE);

	int i;
	int triangleAmount = 20;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(CIRCLEWIDTH);

	glBegin(GL_LINES);
	for (i = triangleAmount; i--;)
	{
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

void drawLine(double initialPointX, double initialPointY, double finalPointX, double finalPointY)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);
	glVertex2f(initialPointX, h - initialPointY);
	glVertex2f(finalPointX, h - finalPointY);
	glEnd();
}

void drawLine(State *initialS, State *finalS)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	double initPointx = initialS->getPos()->x;
	double initPointy = initialS->getPos()->y;
	double finalPointx = finalS->getPos()->x;
	double finalPointy = finalS->getPos()->y;

	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);
	glVertex2f(initPointx * SCALE, h - (initPointy * SCALE));
	glVertex2f(finalPointx * SCALE, h - (finalPointy * SCALE));
	glEnd();
}