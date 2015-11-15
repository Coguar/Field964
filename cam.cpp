#pragma once
#include <SFML/Graphics.hpp>
#include "cam.h"


void getCoord(float x, float y, float x1, float y1) 
{ //функция для считывания координат игрока
	float tempX = x; float tempY = y;
	float tempX1 = x1; float tempY1 = y1;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 128) tempX = 128;
	if (x > 512) tempX = 512;//убираем из вида левую сторону
	if (y < 128) tempY = 128;//верхнюю сторону
	if (y > 512) tempY = 512;
	if (x1 < 128) tempX1 = 128;
	if (x1 > 512) tempX1 = 512;//убираем из вида левую сторону
	if (y1 < 128) tempY1 = 128;//верхнюю сторону
	if (y1 > 512) tempY1 = 512;//нижнюю сторону	

	view1.setCenter(tempX, tempY);
	view2.setCenter(tempX1, tempY1);
	//следим за игроком, передавая его координаты. 
}