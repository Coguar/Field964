#include "stdafx.h"
#include "classEnemy.h"

void Enemy::update(float time, CollisionChecker & checker) {
	xy1 = pos.xy;
	if (properties.health <= 0) {
		properties.life = false;
	}
	if (properties.life == true) {

		xy1.x += Xdir * time;
		if (checker.map_event(getRect1()) == false && player_contact == false ) {
			pos.xy.x = xy1.x;
		}
		xy1.y += Ydir * time;
		if (checker.map_event(getRect1()) == false && player_contact == false ) {
			pos.xy.y = xy1.y;
		}

		if (player_contact == true) {
			sprite->setColor(Color::Red);
		}
		else {
			sprite->setColor(Color::White);
		}

		sprite->setPosition(pos.xy.x, pos.xy.y);
	}
}

FloatRect Enemy::getRect() {
	return FloatRect(pos.xy.x - properties.w / 4, pos.xy.y - properties.h / 4, properties.w / 2, properties.h / 2);
}


FloatRect Enemy::getRect1() {
	return FloatRect(xy1.x - properties.w / 4, xy1.y - properties.h / 4, properties.w / 2, properties.h / 2);
}

bool Enemy::map_event(float y1, float x1) {
	bool wall = 0;
	for (size_t i = 0; i < obj.size(); i++)//проходимся по объектам
		if (FloatRect(x1 - properties.w / 4, y1 - properties.h / 4, properties.h / 2, properties.w / 2).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid") {
				wall = true;
			}
		}
	return wall;
}


float Enemy::getX() {	//этим методом будем забирать координату Х	
	return pos.xy.x;
}
float Enemy::getY() {	//этим методом будем забирать координату Y 	
	return pos.xy.y;
}