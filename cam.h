#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void getCoord(float x, float y, float x1, float y1, View & view1, View & view2)
{ //функция для считывания координат игрока
	float tempX = x; float tempY = y;
	float tempX1 = x1; float tempY1 = y1;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 256) tempX = 256;
	if (x > 2944) tempX = 2944;//убираем из вида левую сторону
	if (y < 256) tempY = 256;//верхнюю сторону
	if (y > 2944) tempY = 2944;
	if (x1 < 256) tempX1 = 256;
	if (x1 > 2944) tempX1 = 2944;//убираем из вида левую сторону
	if (y1 < 256) tempY1 = 256;//верхнюю сторону
	if (y1 > 2944) tempY1 = 2944;//нижнюю сторону	

	view1.setCenter(tempX, tempY);
	view2.setCenter(tempX1, tempY1);
	//следим за игроком, передавая его координаты. 
}