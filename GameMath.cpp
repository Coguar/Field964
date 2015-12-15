#include "stdafx.h"
#include "GameMath.h"
#include <cmath>

float calculateDistantion(float aX, float aY, float bX, float bY){
	return sqrt((aX - bX)*(aX - bX) + (aY - bY)*(aY - bY));
}