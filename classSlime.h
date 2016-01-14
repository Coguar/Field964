#pragma once
#include "classGlobal.h"

class Slime {
public:
	const Vector2f PUDDLE_SIZE = {256, 192};

	PositionObj pos;
	Properties properties;
	bool life;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	sf::String name;
	Image image;
	const int damage = 20;
	float timer = 0;
	const float damage_time = 300;

	const float hit_time = 100;
	float hit_timer = 0;
	bool hit = false;

	
	Slime(float X, float Y) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile("./files/img/slime.png");
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);

		pos.xy.x = X;
		pos.xy.y = Y;
		properties.speed = 3;
		properties.h = PUDDLE_SIZE.y;
		properties.w = PUDDLE_SIZE.x;
		life = true;
		sprite->setOrigin(properties.w / 2, properties.h / 2);
		sprite->setPosition(X, Y);
	}

	void _life_time(float time);
	void _is_hit(float time);
	void update(float time);
	FloatRect getRect();
};