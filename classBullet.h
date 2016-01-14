#pragma once
#include "classGlobal.h"

class Bullet {
public:
	int direction;
	PositionObj pos;
	Properties properties;
	bool life;
	FloatRect puddle_place;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	sf::String name;
	Image image;
	Bullet(String F, String Name, float X, float Y, int fin_x, int fin_y, int dir) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(F);
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);

		name = Name;
		puddle_place = FloatRect(fin_x - 20, fin_y - 20, 40, 40);
		pos.xy.x = X;
		pos.xy.y = Y;
		direction = dir;
		properties.speed = 3;
		properties.w = properties.h = 10;
		life = true;
	}


	void update(float time, CollisionChecker & checker);

	FloatRect getRect();
};