#include "stdafx.h"
#include "GoToTarget.h"
#include <math.h>

void gototarget(int & Xdir, int & Ydir, float aX, float aY, float bX, float bY) {

	if (floor(aX) - floor(bX) == 0) {
		Xdir = 2;
	}
	else if (floor(aX) - floor(bX) > 0) {
		Xdir = 0;
	}
	else if (floor(aX) - floor(bX) < 0) {
		Xdir = 1;
	}

	if (floor(aY) - floor(bY) == 0) {
		Ydir = 2;
	}
	else if (floor(aY) - floor(bY) > 0) {
		Ydir = 0;
	}
	else if (floor(aY) - floor(bY) < 0) {
		Ydir = 1;
	}
}