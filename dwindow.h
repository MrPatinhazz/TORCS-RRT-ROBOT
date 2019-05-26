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
#include "mycar.h"
#include "rrt.h"

using namespace std;

class DWindow
{
    public:
        DWindow(int w, int h, MyCar *mcar, RRT *mrrt);
        ~DWindow();
        void Redisplay();

        void setCarPtr(MyCar *mcar){infoCar = mcar;};
        MyCar* getCarPtr(){return infoCar;};

        void setRRTPtr(RRT *mrrt){inforrt = mrrt;};
        RRT* getRRTPtr(){return inforrt;};

        string getInfoS(){return infoS;};
        void setInfoS(string str){infoS = str;};

    private:
        int statsInt = 0;
        string infoS = "";
        int pathInt = 0;
        MyCar *infoCar;
        RRT *inforrt;        
};

//Stats Window display refresh and text render
void drawWindowStats();
void printText(int x, int y, char *string);

//Path window display refresh and drawings render
void drawWindowPath();
void draw2DProjectedSearchPoints(); //for printing projected state space
void drawMapSegments();
void drawCircle(tPosd point, GLfloat radius);
void drawCircle(v3d pos, GLfloat radius);
void drawLine(double initialPointX, double initialPointY, double finalPointX, double finalPointY);
void drawCubicBezier(tPosd p0, tPosd p1, tPosd p2, tPosd p3, unsigned int numPartialPoints);
GLuint loadTexture(const char * filename);
