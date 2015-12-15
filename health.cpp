#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "health.h"
#include <iostream>
#include <sstream>

void ShowHealth(RenderWindow & window, Text & text, int & health_value, View & view)
{
	text.setString("Здоровье:" + std::to_string(health_value));
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	window.draw(text);
}

void ShowAmmo(RenderWindow & window, Text & text, int & ammo_value, View & view)
{
	if (ammo_value == -1) {
		text.setString("Патроны: --");
	}
	else {
		text.setString("Патроны:" + std::to_string(ammo_value));
	}
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + 30);
	window.draw(text);
}