#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "sprite_position.h"

float AnimationFrame = 0;

void spriteposition(sf::Sprite & sprite, int Xdir, int Ydir, float & time) {
	
	if (Xdir == 0 && Ydir == 0) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(157, 14 + 49 * int(AnimationFrame), 25, 35));
	}
	else if (Xdir == 1 && Ydir == 0) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(261, 13 + 49 * int(AnimationFrame), 25, 35));
	}
	else if (Xdir == 2 && Ydir == 0) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(209, (8 + 49 * int(AnimationFrame)), 25, 35));
	}
	else if (Xdir == 0 && Ydir == 1) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(62, 10 + 49 * int(AnimationFrame), 25, 35));
	}
	else if (Xdir == 1 && Ydir == 1) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(356, 10 + 49 * int(AnimationFrame), 25, 35));
	}
	else if (Xdir == 2 && Ydir == 1) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(13, (9 + 49 * int(AnimationFrame)), 25, 35));
	}
	else if (Xdir == 0 && Ydir == 2) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(111, (9 + 49 * int(AnimationFrame)), 25, 35));
	}
	else if (Xdir == 1 && Ydir == 2) {
		AnimationFrame += 0.004 * time;
		if (AnimationFrame > 4) AnimationFrame -= 4;
		sprite.setTextureRect(IntRect(310, (9 + 49 * int(AnimationFrame)), 25, 35));
	}
	else if (Xdir == 2 && Ydir == 2) {
		sprite.setTextureRect(IntRect(310, (9 + 49 * int(AnimationFrame)), 25, 35));
	}
}