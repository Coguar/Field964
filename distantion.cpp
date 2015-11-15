#include "stdafx.h"
#include "distantion.h"
#include <cmath>

float calculateDistantion(float aX, float aY, float bX, float bY){
	return abs(aX - bX) + abs(aY - bY);
}