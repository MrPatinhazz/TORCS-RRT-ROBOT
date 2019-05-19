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
