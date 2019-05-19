#include "dwindow.h"

static string infoString;

DWindow::DWindow()
{
    glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_CONTINUE_EXECUTION
	);

	glutInitWindowSize(600, 300);
	statsInt = glutCreateWindow("Stats");
	glutPositionWindow(720,0);
	glutDisplayFunc(drawWindow);
	std::cout<< "Statswindow int: " << statsInt<< std::endl;
}

DWindow::~DWindow()
{
    glutDestroyWindow(statsInt);
}

void DWindow::Redisplay()
{
    int gameplayWindow = glutGetWindow();
	glutSetWindow(statsInt);
    infoString = getInfoS();
	glutPostRedisplay();
	glutSetWindow(gameplayWindow);
}

void drawWindow()
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