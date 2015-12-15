#include "classBullet.h"

void Bullet::update(float time)
{

	pos.xy.x += pos.dx * time * 10;
	pos.xy.y += pos.dy * time * 10;

	if (pos.xy.x <= 0) pos.xy.x = 1;
	if (pos.xy.y <= 0) pos.xy.y = 1;

	for (size_t i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect))
		{
			life = false;
		}
	}

	sprite->setPosition(pos.xy.x + properties.w / 2, pos.xy.y + properties.h / 2);
}

FloatRect Bullet::getRect() {
	return FloatRect(pos.xy.x, pos.xy.y, properties.h, properties.w);
}