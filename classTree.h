#pragma once
#include "classGlobal.h"

class Tree {
public:
	int Name;
	float x, y;
	float w = 512.0;
	float h = 512.0;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	sf::String name;
	Image image;
	Tree(String F, float X, float Y) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		x = X;
		y = Y;
		sprite->setPosition(x, y);
		sprite->setOrigin(w / 2, h / 2);
	}
	FloatRect getRect();
};