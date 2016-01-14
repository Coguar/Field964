#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "control.h"

float CurrentFrame, CurrentFrame1 = 0;

void controlPlayer(Sprite & sprite, int & dir, float & speed, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down)
{

	if (Keyboard::isKeyPressed(go_left))
	{
		dir = 1; speed = 1.5;
	}
	if (Keyboard::isKeyPressed(go_right))
	{
		dir = 0; speed = 1.5;

	}
	if (Keyboard::isKeyPressed(go_up))
	{
		dir = 3; speed = 1.5;

		if (Keyboard::isKeyPressed(go_left))
		{
			dir = 6; speed = 1.5;

		}
		if (Keyboard::isKeyPressed(go_right))
		{
			dir = 5; speed = 1.5;

		}
	}
	if (Keyboard::isKeyPressed(go_down))
	{
		dir = 2; speed = 1.5;

		if (Keyboard::isKeyPressed(go_left))
		{
			dir = 7; speed = 1.5;

		}
		if (Keyboard::isKeyPressed(go_right))
		{
			dir = 4; speed = 1.5;


		}
	}
}