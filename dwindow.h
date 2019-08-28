/***************************************
 * 
 *          DBG WINDOW CLASS             
 * 
 * ************************************/
#pragma once

#include <iostream>
#include <stdio.h>
#include <cstring>
#include "GL/freeglut.h"
#include "berniw.h"

using namespace std;

class RRT;
class DWindow
{
    public:
        DWindow(int w, int h, MyCar*, RRT*, TrackDesc*, Pathfinder*);
        ~DWindow();
        void Redisplay();

        string getInfoS(){return infoS;};
        void setInfoS(string str){infoS = str;};

    private:
        int statsInt = 0;
        string infoS = "";
        int pathInt = 0;
};

//Stats Window display refresh and text render
void drawWindowStats();
void printText(int x, int y, char *string);

//Path window display refresh and drawings render
void drawWindowPath();
void drawMapSegments();
void drawCircle(tPosd point, GLfloat radius);
void drawCircleP(v3d* pos, GLfloat radius);
void drawLine(double initialPointX, double initialPointY, double finalPointX, double finalPointY);
void drawLine(State* initialS, State* finalS);
GLuint loadTexture(const char * filename);
