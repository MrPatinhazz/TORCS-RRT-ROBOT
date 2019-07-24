#include "dwindow.h"

string infoString;
float _scale = 1;
MyCar* dwCar;
RRT* dwRRT;
TrackDesc* dwTrDesc;
Pathfinder* dwPf;
int nTSeg = 0;

DWindow::DWindow(int w, int h, MyCar* mcar, RRT* mrrt, TrackDesc* mtdesc, Pathfinder* mpf)
{
    glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_CONTINUE_EXECUTION
	);

	dwCar = mcar;
	dwRRT = mrrt;
	dwTrDesc = mtdesc;
	dwPf = mpf;

	glutInitWindowSize(600,300);
	statsInt = glutCreateWindow("Stats");
	glutPositionWindow(720,0);
	glutDisplayFunc(drawWindowStats);

	glutInitWindowSize(w*_scale,h*_scale);
	pathInt = glutCreateWindow("Drawing path");
	glutPositionWindow(720,200);
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
		int x = 10; int y = 30;
		printText(x, y, (char*)infoString.c_str());

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
	glColor3f(1,0,1);

	//Draws car current position every frame
	drawCircle(dwCar->getCarPtr()->pub.DynGCg.pos,2);

	glColor3f(1,1,0);

	//Draws states position every frame
	vector <State*> dwPool = dwRRT->getStatePool();
	if(!dwPool.empty())
	{
		for(vector<State*>::size_type j = 0; j < dwPool.size(); j++)
		{
			drawCircleP(dwPool[j]->getPos(),2);
		}
	}

	//Draw map segments
	drawMapSegments();

	//DRAWING CYCLE
	
	glPopMatrix();
	glutSwapBuffers();
}

void drawMapSegments()
{
	glColor3f(0.0,0.0,0.0);
	nTSeg = dwTrDesc->getnTrackSegments();
	for (int i = 0; i <= nTSeg; i=i+7)
	{
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getLeftBorder(),0.5);
		drawCircleP(dwTrDesc->getSegmentPtr(i)->getRightBorder(),0.5);
	}
}

void drawCircle(tPosd point, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (point.x * _scale);
	int y = h - (point.y * _scale);

	int i;
	int triangleAmount = 30;
	GLfloat twicePi = 2.0f * PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex2f(x, y);
			glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
}

void drawCircleP(v3d pos, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (pos.x * _scale);
	int y = h - (pos.y * _scale);

	int i;
	int triangleAmount = 30;
	GLfloat twicePi = 2.0f * PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex2f(x, y);
			glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
}

void drawCircleP(v3d* pos, GLfloat radius)
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	int x = (pos->x * _scale);
	int y = h - (pos->y * _scale);

	int i;
	int triangleAmount = 10;
	GLfloat twicePi = 2.0f * PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);

	glBegin(GL_LINES);
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex2f(x, y);
			glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
}