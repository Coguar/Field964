#include "stdafx.h"
#include "classBullet.h"

void Bullet::update(float time, CollisionChecker & checker)
{

	pos.xy.x += pos.dxy.x * time * 10;
	pos.xy.y += pos.dxy.y * time * 10;

	if (pos.xy.x <= 0) pos.xy.x = 1;
	if (pos.xy.y <= 0) pos.xy.y = 1;

	if (name == "Spite") {
		if (getRect().intersects(puddle_place)) {
			life = false;
		}
	}
	else {
		if (checker.map_event(getRect()) == true)
		{
			life = false;
		}
	}
	sprite->setPosition(pos.xy.x + properties.w / 2, pos.xy.y + properties.h / 2);
}

FloatRect Bullet::getRect() {
	return FloatRect(pos.xy.x, pos.xy.y, properties.h, properties.w);
}