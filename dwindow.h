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

using namespace std;

class DWindow
{
    public:
        DWindow();
        ~DWindow();
        void Redisplay();
        void setCarPtr(MyCar *car){wCar = car;};
        MyCar* getCarPtr(){return wCar;};
        string getInfoS(){return infoS;};
        void setInfoS(string str){infoS = str;};

    private:
        int statsInt = 0;
        string infoS = "";
        MyCar *wCar;        
        
};

void drawWindow();
void printText(int x, int y, char *string);
void drawSearchPoints();
void draw2DProjectedSearchPoints(); //for printing projected state space
void drawMapSegments();
void drawCircle(tPosd point, GLfloat radius);
void drawLine(double initialPointX, double initialPointY, double finalPointX, double finalPointY);
void drawCubicBezier(tPosd p0, tPosd p1, tPosd p2, tPosd p3, unsigned int numPartialPoints);
GLuint loadTexture(const char * filename);
