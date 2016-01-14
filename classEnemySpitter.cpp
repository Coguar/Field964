#include "stdafx.h"
#include "classEnemySpitter.h"

void Spitter::_check_spit(float time, float p_pos_x, float p_pos_y) {
	recovery_spittle += time;
	if (recovery_spittle >= recovery_time) {
		recovery_spittle = 0;
	}
}

void Spitter::update(float time, CollisionChecker & checker, float p_pos_x, float p_pos_y) {
	
	_check_spit(time, p_pos_x, p_pos_y);

	xy1 = pos.xy;
	if (properties.health <= 0) {
		properties.life = false;
	}
	if (properties.life == true) {

		xy1.x += dir.x * time;
		if (checker.map_event(getRect1()) == false && player_contact == false) {
			pos.xy.x = xy1.x;
		}
		xy1.y += dir.x * time;
		if (checker.map_event(getRect1()) == false && player_contact == false) {
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

FloatRect Spitter::getRect() {
	return FloatRect(pos.xy.x - properties.w / 4, pos.xy.y - properties.h / 4, properties.w / 2, properties.h / 2);
}


FloatRect Spitter::getRect1() {
	return FloatRect(xy1.x - properties.w / 4, xy1.y - properties.h / 4, properties.w / 2, properties.h / 2);
}

float Spitter::getX() {	//этим методом будем забирать координату Х	
	return pos.xy.x;
}
float Spitter::getY() {	//этим методом будем забирать координату Y 	
	return pos.xy.y;
}