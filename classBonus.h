#pragma once
#include "classGlobal.h"

class Bonus {
private:
	std::map<int, IntRect> bonus_rect =
	{ { 1, IntRect(0, 0, 32, 32) },
	{ 2, IntRect(32, 0, 32, 32) },
	{ 3, IntRect(64, 0, 32, 32) },
	{ 4, IntRect(128, 0, 32, 32) },
	{ 5, IntRect(160, 0, 32, 32) },
	{ 6, IntRect(192, 0, 32, 32) },
	{ 7, IntRect(0, 32, 32, 32) },
	{ 8, IntRect(32, 32, 128, 32) },
	{ 9, IntRect(0, 64, 128, 64) },
	{ 10, IntRect(96, 0, 32, 32) }
	};
public:
	int Name;
	PositionObj pos;
	Properties properties;

	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	sf::String name;
	Image image;
	Bonus(String F, int name1, float X, float Y) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		pos.xy.x = X;
		pos.xy.y = Y;
		Name = name1;
		properties.w = properties.h = 32;
		sprite->setTextureRect(bonus_rect[Name]);
		sprite->setPosition(pos.xy.x, pos.xy.y);
		sprite->setOrigin(properties.w / 2, properties.h / 2);
	}
	FloatRect getRect();
};