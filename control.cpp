#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "control.h"

float CurrentFrame, CurrentFrame1 = 0;

void controlPlayer(Sprite & sprite, int & dir, float & speed, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down,int w)
{
	if (Keyboard::isKeyPressed(go_left))
	{
		dir = 1; speed = 1;
		CurrentFrame += 0.04 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(310, (9 + 49 * int(CurrentFrame)), w, 35));
	}
	if (Keyboard::isKeyPressed(go_right))
	{
		dir = 0; speed = 1;
		CurrentFrame += 0.04 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(111, (9 + 49 * int(CurrentFrame)), w, 35));

	}
	if (Keyboard::isKeyPressed(go_up))
	{
		dir = 3; speed = 1;
		sprite.setTextureRect(IntRect(13, 7, 25, 35));
		CurrentFrame += 0.04 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(13, (9 + 49 * int(CurrentFrame)), w, 35));
		if (Keyboard::isKeyPressed(go_left))
		{
			dir = 6; speed = 1;
			CurrentFrame1 += 0.04 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(356, 10 + 49 * int(CurrentFrame1), w, 35));
		}
		if (Keyboard::isKeyPressed(go_right))
		{
			dir = 5; speed = 1;
			CurrentFrame1 += 0.04 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(62, 10 + 49 * int(CurrentFrame1), w, 35));
		}
	}
	if (Keyboard::isKeyPressed(go_down))
	{
		dir = 2; speed = 1;
		sprite.setTextureRect(IntRect(13, 7, w, 35));
		CurrentFrame += 0.04 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(209, (8 + 49 * int(CurrentFrame)), w, 35));
		if (Keyboard::isKeyPressed(go_left))
		{
			dir = 7; speed = 1;
			CurrentFrame1 += 0.04 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(261, 13 + 49 * int(CurrentFrame1), w, 35));
		}
		if (Keyboard::isKeyPressed(go_right))
		{
			dir = 4; speed = 1;
			CurrentFrame1 += 0.04 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(157, 14 + 49 * int(CurrentFrame1), w, 35));
		}
	}
}