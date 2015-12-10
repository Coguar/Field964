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
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);//задаем позицию текста, отступа€ от центра камеры
	window.draw(text);//рисую этот тексn
}

void ShowAmmo(RenderWindow & window, Text & text, int & ammo_value, View & view)
{
	std::ostringstream playerHealthString;    // объ€вили переменную
	playerHealthString << ammo_value;		//занесли в нее число здоровь€, то есть формируем строку
	if (ammo_value == -1) {
		text.setString("ѕатроны: Ќеограничено");
	}
	else {
		text.setString("ѕатроны:" + playerHealthString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	}
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + 30);//задаем позицию текста, отступа€ от центра камеры
	window.draw(text);//рисую этот тексn
}