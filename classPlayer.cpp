#include "stdafx.h"
#include "classPlayer.h"
void Player::_chose_gun() {

	weapoons = m_Guns[gun];
}

void Player::_take_gun() {
	switch (weapoons) {
	case pistol: 
		auto_gun = false; image.loadFromFile("./files/sprites/player_pistol.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
		damage = damage_pistol + bonus_damage;  ammo = -1; break;
	case uzi:
		auto_gun = true; image.loadFromFile("./files/sprites/player_uzi.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
			  damage = damage_uzi + bonus_damage; ammo = ammo_uzi;  break;
	case shotgun:
		auto_gun = false; image.loadFromFile("./files/sprites/player_shotgun.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
				 damage = damage_shotgun + bonus_damage; ammo = ammo_shootgun;  break;
	case machinegun:
		auto_gun = true; image.loadFromFile("./files/sprites/player_machinegun.png"); texture->loadFromImage(image);
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
	case left: pos.dxy.x = speed; pos.dxy.y = 0;   break;
	case right: pos.dxy.x = -speed; pos.dxy.y = 0;   break;
	case up: pos.dxy.x = 0; pos.dxy.y = speed;   break;
	case down: pos.dxy.x = 0; pos.dxy.y = -speed;   break;
	case u_left: pos.dxy.x = float(speed * 0.66); pos.dxy.y = float(speed * 0.66);   break;
	case u_right: pos.dxy.x = float(speed * 0.66); pos.dxy.y = float(-speed * 0.66);   break;
	case d_left: pos.dxy.x = float(-speed * 0.66); pos.dxy.y = float(-speed * 0.66);   break;
	case d_right: pos.dxy.x = float(-speed * 0.66); pos.dxy.y = float(speed * 0.66);   break;
	}
}

void Player::_steps(sf::Sound & sound) {
	if (properties.speed != 0 && !properties.isGoing) {
		sound.play();
		properties.isGoing = true;

	}
	else if (properties.speed == 0){
		sound.pause();
		properties.isGoing = false;

	}
}

void Player::_is_die(sf::Sound & sound) {
	if (properties.health <= 0) {
		if (properties.life) {
			sound.play();
		}
		properties.life = false;
	}
}

void Player::update(float time, CollisionChecker & checker, sf::Sound & sound, sf::Sound & dead_sound, sf::Sound & win_sound) {

	xy1 = pos.xy;
	_steps(sound);

	_chose_gun();
	_take_gun();
	_set_speed();
	_quest_progress(checker, win_sound);
	xy1.x += pos.dxy.x * time;
	xy1.y += pos.dxy.y * time;

	if (checker.map_event(getRect1()) == false && !contact) {
		pos.xy.x = xy1.x;
		pos.xy.y = xy1.y;
	}

	properties.speed = 0;

	_is_die(dead_sound);

	if (properties.life == false) {
		properties.health = 0;
	}
	sprite->setPosition(pos.xy.x, pos.xy.y);

}

FloatRect Player::getRect() {
	return FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.h, properties.w);
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


void Player::_quest_progress(CollisionChecker & checker, sf::Sound & win_sound) {
	if (checker.quest_event(getRect1(), "car") && quest == start) {
		quest = find_car;
		quest_move = true;
	}
	else if (checker.quest_event(getRect(), "gaz") && quest == find_car) {
		quest = find_gaz;
		if (take_bucket == true) {
			quest = find_colon;
		}
		quest_move = true;
	}
	else if (checker.quest_event(getRect(), "bucket") && quest == find_busket) {
		quest = find_colon;
	}
	else if (checker.quest_event(getRect(), "colon") && quest == find_colon) {
		quest = go_to_car;
		quest_move = true;
	}
	else if (checker.quest_event(getRect(), "car") && quest == go_to_car) {
		quest = finish;
		win_sound.play();
	}
	if (quest == find_gaz && take_bucket == true) {
		quest = find_busket;
	}
}