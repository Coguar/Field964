#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "health.h"
#include <iostream>
#include <sstream>

void ShowHealth(RenderWindow & window, Text & text, int & health_value, View & view)
{
	std::ostringstream playerHealthString;    // объ€вили переменную
	playerHealthString << health_value;		//занесли в нее число здоровь€, то есть формируем строку
	text.setString("«доровье:" + playerHealthString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text.setPosition(view.getCenter().x - 256, view.getCenter().y - 256);//задаем позицию текста, отступа€ от центра камеры
	window.draw(text);//рисую этот тексn
}