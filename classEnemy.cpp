#include "stdafx.h"
#include "classEnemy.h"

void Enemy::_check_spit(float time, float p_pos_x, float p_pos_y) {
	recovery_spittle += time;
	if (recovery_spittle >= recovery_time) {
		recovery_spittle = 0;
		shooting = true;
	}
}

void Enemy::_is_hit(float time) {
	if (hit == false) {
		hit_timer += time;
	}
	if (hit_timer >= hit_time) {
		hit = true;
		hit_timer = 0;
	}
}

void Enemy::update(float time, CollisionChecker & checker, float p_pos_x, float p_pos_y) {
	_is_hit(time);
	xy1 = pos.xy;
	if (properties.health <= 0) {
		properties.life = false;
	}
	if (properties.life == true) {
		if (Name == "spitter") {
			_check_spit(time, p_pos_x, p_pos_y);
		}
		xy1.x += dir.x * time * properties.speed;
		if (checker.map_event(getRect1()) == false && player_contact == false) {
			pos.xy.x = xy1.x;
		}
		xy1.y += dir.y * time * properties.speed;
		if (checker.map_event(getRect1()) == false && player_contact == false) {
			pos.xy.y = xy1.y;
		}

		if (angry) {
			sprite->setPosition(pos.xy.x, pos.xy.y);
		}
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