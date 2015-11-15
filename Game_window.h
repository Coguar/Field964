#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>


struct Game_window
{
		sf::RenderWindow * window;
		int heigth, width;
	
		Game_window(sf::RenderWindow & window, int heigth, int width) 
		{
			this->window = &window;
			this->heigth = heigth;
			this->width = width;

		}
};
