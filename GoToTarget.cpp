#include "stdafx.h"
#include "GoToTarget.h"
#include <iostream>
#include "SFML\Graphics.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

void gototarget(float & dx, float & dy, float aX, float aY, float bX, float bY) {
	float distance = sqrt((aX - bX)*(aX - bX) + (aY - bY)*(aY - bY));

	dx = (aX - bX) / distance;
	dy = (aY - bY) / distance;
}