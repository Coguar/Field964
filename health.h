#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>


using namespace sf;

void ShowHealth(RenderWindow & window, Text & text, int & health_value, View & view);

void ShowAmmo(RenderWindow & window, Text & text, int & ammo_value, View & view);
