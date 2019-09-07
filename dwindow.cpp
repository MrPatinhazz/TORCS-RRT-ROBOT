#include "dwindow.h"

#define MAPSEGWIDTH 0.5
#define CIRCLEWIDTH 5
#define LINEWIDTH 1.2
#define SCALE 1.5

//GLCOLORS
#define WHITE 1,1,1
#define BLACK 0,0,0
#define LGTGREY 0.839, 0.839, 0.839
#define RED 1,0,0 
#define ORANGE 1, 0.631, 0.058
#define PURPLE 1, 0.160, 0.956
#define BLUE 0,0,1
#define GREEN 0, 0.501, 0.062
#define YELLOW 1,1,0

string infoString;

MyCar *dwCar;
RRT *dwRRT;
TrackDesc *dwTrDesc;
Pathfinder *dwPf;
OtherCar *dwOcar;
Situation *dwSit;
int nTSeg = 0;
const GLfloat twicePi = PI * 2.0f;

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

	glutInitWindowSize(300, 300);
	statsInt = glutCreateWindow("Stats");
	glutPositionWindow(720, 0);
	glutDisplayFunc(drawStatsWindow);

	glutInitWindowSize(w * SCALE, h * SCALE);
	pathInt = glutCreateWindow("Drawing path");
	glutPositionWindow(690, 0);
	glutDisplayFunc(drawPathWindow);
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
	infoString = getInfoS();
	int gameplayWindow = glutGetWindow();

	glutSetWindow(statsInt);
	glutPostRedisplay();

	glutSetWindow(pathInt);
	glutPostRedisplay();

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
	glColor3f(BLACK);
	drawMapSegments();

	//Draw Plan
	//glColor3f(PURPLE);
	//drawPlan();

	//Draws other cars current position
	for(int j = dwSit->raceInfo.ncars; j--;)
	{
		glColor3f(ORANGE);
		drawCircleP(dwOcar[j].getCurrentPos(),2);
		glColor3f(BLUE);
		drawHitbox(dwOcar[j].getCarPtr());
	}

	//Draws own car current position
	glColor3f(RED);
	drawCircleP(dwCar->getCurrentPos(),2);

	//Draws states position and connections
	drawRRT();

	glPopMatrix();
	glutSwapBuffers();
}

void drawMapSegments()
{
	nTSeg = dwTrDesc->getnTrackSegments();
	for (int i = 0; i <= nTSeg; i = i + 7)
	{
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getLeftBorder(), MAPSEGWIDTH);
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getRightBorder(), MAPSEGWIDTH);
	}
}

void drawPlan()
{
	for(int i = 0; i <= dwPf->getnPathSeg(); i = i + 7)
	{
		drawCircleP(dwPf->getPathSeg(i)->getOptLoc(),0.8);
	}
};

void drawRRT()
{
	vector<State *> dwPool = dwRRT->getPool();
	if (!dwPool.empty())
	{
		for (size_t j = dwPool.size(); j--;)
		{
			glColor3f(YELLOW);
			drawCircleP(dwPool[j]->getPos(), 1);

			//Draws trees connections (edges)
			glColor3f(GREEN);
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

void drawHitbox(tCarElt *car)
{
	for(int c = 4; c--;)
	{
		drawCircle(car->pub.corner[c],1.5);
	}
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

//TODO: RENDER TO TEXTURE MAP SEGMENTSS