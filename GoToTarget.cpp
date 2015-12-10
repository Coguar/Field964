#include "stdafx.h"
#include "GoToTarget.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

void gototarget(float & Xdir, float & Ydir, float aX, float aY, float bX, float bY) {
	
	float distance = sqrt((aX - bX)*(aX - bX) + (aY - bY)*(aY - bY));

	Xdir = (aX - bX) / distance;
	Ydir = (aY - bY) / distance;
}

void gototargetShot(float & Xdir, float & Ydir, float aX, float aY, float bX, float bY) {


	/*float distance = sqrt((aX - bX)*(aX - bX) + (aY - bY)*(aY - bY));
	float r = sqrt(pow(aX - bX, 2) + pow(aY - (bY + distance), 2)) / 2;
	double degree = 57.2958 * acos((2 * pow(distance, 2) - pow(r, 2)) / (2 * pow(distance, 2)));

	std::cout << degree << std::endl;

	float X1 = bX + (distance * cos((degree - 15 + i * 5) * M_PI / 180));
	float Y1 = bY + (distance * sin((degree - 15 + i * 5) * M_PI / 180));

	Xdir = (X1 - bX) / distance;//идем по иксу с помощью вектора нормали
	Ydir = (Y1 - bX) / distance;//идем по игреку так же*/

	float distance = sqrt((aX - bX)*(aX - bX) + (aY - bY)*(aY - bY));
	float X = (aX - bX);

	Xdir = (aX - bX) / 50;//идем по иксу с помощью вектора нормали
	Ydir = (aY - bY) / 50;//идем по игреку так же

}