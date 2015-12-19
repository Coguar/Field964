#include "stdafx.h"
#include "classPlayer.h"

void Player::_chose_gun() {

	weapoons = m_Guns[gun];
}

void Player::_take_gun() {
	switch (weapoons) {
	case pistol: image.loadFromFile("./files/sprites/player_pistol.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
		damage = damage_pistol + bonus_damage;  ammo = -1; break;
	case uzi:
		image.loadFromFile("./files/sprites/player_uzi.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
			  damage = damage_uzi + bonus_damage; ammo = ammo_uzi;  break;
	case shotgun:
		image.loadFromFile("./files/sprites/player_shotgun.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
				 damage = damage_shotgun + bonus_damage; ammo = ammo_shootgun;  break;
	case machinegun:
		image.loadFromFile("./files/sprites/player_machinegun.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
					 damage = damage_machinegun + bonus_damage; ammo = ammo_machinegun;  break;
	}
}


void Player::_set_speed() {
	float speed = properties.speed;
	if (quest == go_to_car) {
		speed = properties.speed * 0.5f;
	}
	step_to = dir_variant[dir];
	switch (step_to) {
	case left: pos.dx = speed; pos.dy = 0;   break;
	case right: pos.dx = -speed; pos.dy = 0;   break;
	case up: pos.dx = 0; pos.dy = speed;   break;
	case down: pos.dx = 0; pos.dy = -speed;   break;
	case u_left: pos.dx = float(speed * 0.66); pos.dy = float(speed * 0.66);   break;
	case u_right: pos.dx = float(speed * 0.66); pos.dy = float(-speed * 0.66);   break;
	case d_left: pos.dx = float(-speed * 0.66); pos.dy = float(-speed * 0.66);   break;
	case d_right: pos.dx = float(-speed * 0.66); pos.dy = float(speed * 0.66);   break;
	}
}

void Player::update(float time, CollisionChecker & checker) {
	xy1 = pos.xy;

	_chose_gun();
	_take_gun();
	_set_speed();
	_quest_progress(xy1.y, xy1.x);
	xy1.x += pos.dx * time;
	xy1.y += pos.dy * time;

	if (checker.map_event(getRect1()) == false) {
		pos.xy.x = xy1.x;
		pos.xy.y = xy1.y;
	}

	properties.speed = 0;

	if (properties.health <= 0) {
		properties.life = false;
	}

	if (properties.life == false) {
		properties.health = 0;
	}
	sprite->setPosition(pos.xy.x, pos.xy.y);

}

FloatRect Player::getRect() {
	return FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.h, properties.w);
	std::cout << properties.h << std::endl;
}

FloatRect Player::getRect1() {
	return FloatRect(xy1.x - properties.w / 2, xy1.y - properties.h / 2, properties.h, properties.w);
}

float Player::getX() {
	return pos.xy.x;
}
float Player::getY() {
	return pos.xy.y;
}



bool Player::_map_event(float y1, float x1) {
	bool wall = 0;
	for (size_t i = 0; i < obj.size(); i++)
		if (getRect1().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid") {
				wall = true;
			}
		}
	return wall;
}

void Player::_quest_progress(float y1, float x1) {
	for (size_t i = 0; i < obj.size(); i++)//проходимся по объектам
		if (FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.h, properties.w).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "car" && quest == start) {
				quest = find_car;
			}
			else if (obj[i].name == "gaz" && quest == find_car) {
				if (take_bucket == true) {
					quest = find_colon;
				}
				else {
					quest = find_busket;
				}
			}
			else if (obj[i].name == "bucket" && quest == find_busket) {
				quest = find_colon;
			}
			else if (obj[i].name == "colon" && quest == find_colon) {
				quest = go_to_car;
			}
			else if (obj[i].name == "car" && quest == go_to_car) {
				quest = finish;
			}
		}
}