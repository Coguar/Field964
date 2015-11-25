#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void getCoord(float x, float y, View & view1)
{ //функция для считывания координат игрока
	float tempX = x; float tempY = y;

	if (x < view1.getSize().x / 2) tempX = view1.getSize().x / 2;
	if (x > 1600 - view1.getSize().x / 2) tempX = 1600 - view1.getSize().x / 2;//убираем из вида левую сторону
	if (y < view1.getSize().y / 2) tempY = view1.getSize().y / 2;//верхнюю сторону
	if (y > 1600 - view1.getSize().y / 2) tempY = 1600 - view1.getSize().y / 2;

	view1.setCenter(tempX, tempY);
	//следим за игроком, передавая его координаты. 
}