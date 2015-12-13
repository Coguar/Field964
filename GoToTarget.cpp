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