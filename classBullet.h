#pragma once
#include "classGlobal.h"

class Bullet {
public:
	std::vector<Object> obj;
	int direction;
	PositionObj pos;
	Properties properties;
	bool life;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	sf::String name;
	Image image;
	Bullet(String F, String Name, Level &lvl, float X, float Y, int W, int H, int dir) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(F);
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);

		obj = lvl.GetObjects("solid");
		pos.xy.x = X;
		pos.xy.y = Y;
		direction = dir;
		properties.speed = 3;
		properties.w = properties.h = 5;
		life = true;
	}


	void update(float time);

	FloatRect getRect();
};