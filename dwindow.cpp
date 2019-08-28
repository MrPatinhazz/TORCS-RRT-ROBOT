#include "dwindow.h"

#define MAPSEGWIDTH 1
#define CIRCLEWIDTH 5
#define LINEWIDTH 1
#define SCALE 0.5

string infoString;

MyCar *dwCar;
RRT *dwRRT;
TrackDesc *dwTrDesc;
Pathfinder *dwPf;
int nTSeg = 0;
const GLfloat twicePi = PI*2.0f; 

DWindow::DWindow(int w, int h, MyCar *mcar, RRT *mrrt, TrackDesc *mtdesc, Pathfinder *mpf)
{
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_CONTINUE_EXECUTION);

	dwCar = mcar;
	dwRRT = mrrt;
	dwTrDesc = mtdesc;
	dwPf = mpf;

	glutInitWindowSize(600, 300);
	statsInt = glutCreateWindow("Stats");
	glutPositionWindow(720, 0);
	glutDisplayFunc(drawWindowStats);

	glutInitWindowSize(w * SCALE, h * SCALE);
	pathInt = glutCreateWindow("Drawing path");
	glutPositionWindow(720, 200);
	glutDisplayFunc(drawWindowPath);
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
void drawWindowStats()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glColor3f(0, 0, 0);
	int x = 10;
	int y = 30;
	printText(x, y, (char *)infoString.c_str());

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
void drawWindowPath()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7, 0.7, 0.7, 0.7);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	//DRAWING CYCLE
	glColor3f(1, 0, 1);

	//Draw map segments
	drawMapSegments();

	//Draws car current position
	drawCircle(dwCar->getCarPtr()->pub.DynGCg.pos, 2);

	//Draws states position and connections
	vector<State *> dwPool = dwRRT->getPool();
	if (!dwPool.empty())
	{
		for (size_t j = dwPool.size(); j--;)
		{
			glColor3f(1, 1, 0);
			drawCircleP(dwPool[j]->getPos(), 1);

			//Draws trees connections (edges)
			glColor3f(1, 0, 0);
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

	//DRAWING CYCLE

	glPopMatrix();
	glutSwapBuffers();
}

void drawMapSegments()
{
	glColor3f(0, 0, 0);
	nTSeg = dwTrDesc->getnTrackSegments();
	for (int i = 0; i <= nTSeg; i = i + 7)
	{
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getLeftBorder(), MAPSEGWIDTH);
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getRightBorder(), MAPSEGWIDTH);
	}
}

void drawCircle(tPosd point, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (point.x * SCALE);
	int y = h - (point.y * SCALE);

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