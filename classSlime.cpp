#include "stdafx.h"
#include "classSlime.h"


void Slime::_life_time(float time) {
	timer += time;
	if (timer >= damage_time) {
		life = false;
		timer = 0;
	}
}

void Slime::_is_hit(float time) {
	hit_timer += time;
	if (hit_timer >= hit_time) {
		hit = true;
		hit_timer = 0;
	}
}

void Slime::update(float time)
{
	_life_time(time);
	_is_hit(time);
}

FloatRect Slime::getRect() {
	return FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.w, properties.h);
}