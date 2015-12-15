#pragma once
#include <SFML/Graphics.hpp>
#include "level.h"
#include <map>
#include <memory>

/*#include "classPlayer.h"
#include "classEnemy.h"
#include "classBullet.h"*/

using namespace sf;

struct PositionObj
{
	float dx;
	float dy;

	Vector2f xy;

};

struct Properties
{
	float speed;
	float moveTimer;

	float w;
	float h;
	int health;

	bool life;
	sf::String name;
};

class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	PositionObj pos;
	Properties properties;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Entity(sf::Image & image, sf::String Name, float X, float Y, float W, float H) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		pos.xy.x = X; pos.xy.y = Y; properties.w = W; properties.h = H; properties.name = Name; properties.moveTimer = 0;
		properties.speed = 0; properties.health = 100; pos.dx = 0; pos.dy = 0;
		properties.life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(properties.w / 2, properties.h / 2);
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.h, properties.w);
	}
};

/*class Bullet {
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


	void update(float time)
	{

		pos.xy.x += pos.dx * time * 10;
		pos.xy.y += pos.dy * time * 10;

		if (pos.xy.x <= 0) pos.xy.x = 1;
		if (pos.xy.y <= 0) pos.xy.y = 1;

		for (size_t i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}

		sprite->setPosition(pos.xy.x + properties.w / 2, pos.xy.y + properties.h / 2);
	}

	FloatRect getRect() {
		return FloatRect(pos.xy.x, pos.xy.y, properties.h, properties.w);
	}
};*/

//class Bonus {
//private:
//	std::map<int, IntRect> bonus_rect =
//	{ { 1, IntRect(0, 0, 32, 32) },
//		{ 2, IntRect(32, 0, 32, 32) },
//		{ 3, IntRect(64, 0, 32, 32) },
//		{ 4, IntRect(128, 0, 32, 32) },
//		{ 5, IntRect(160, 0, 32, 32) },
//		{ 6, IntRect(192, 0, 32, 32) },
//		{ 7, IntRect(0, 32, 32, 32) },
//		{ 8, IntRect(32, 32, 128, 32) },
//		{ 9, IntRect(0, 64, 128, 64) },
//		{ 10, IntRect(96, 0, 32, 32) }
//	};
//public:
//	int Name;
//	PositionObj pos;
//	Properties properties;
//
//	std::shared_ptr<Texture> texture;
//	std::shared_ptr<Sprite> sprite;
//	sf::String name;
//	Image image;
//	Bonus(String F, int name1, float X, float Y) {
//		texture = std::make_shared<Texture>();
//		sprite = std::make_shared<Sprite>();
//		image.loadFromFile(F);
//		texture->loadFromImage(image);
//		sprite->setTexture(*texture);
//		pos.xy.x = X;
//		pos.xy.y = Y;
//		Name = name1;
//		sprite->setTextureRect(bonus_rect[name1]);
//		sprite->setPosition(pos.xy.x, pos.xy.y);
//		sprite->setOrigin(properties.w / 2, properties.h / 2);
//	}
//	FloatRect getRect() {
//		return FloatRect(pos.xy.x, pos.xy.y, 32, 32);
//	}
//};

//class Tree {
//public:
//	int Name;
//	float x, y;
//	float w = 512.0;
//	float h = 512.0;
//	std::shared_ptr<Texture> texture;
//	std::shared_ptr<Sprite> sprite;
//	sf::String name;
//	Image image;
//	Tree(String F, float X, float Y) {
//		texture = std::make_shared<Texture>();
//		sprite = std::make_shared<Sprite>();
//		image.loadFromFile(F);
//		texture->loadFromImage(image);
//		sprite->setTexture(*texture);
//		x = X;
//		y = Y;
//		sprite->setPosition(x, y);
//		sprite->setOrigin(w / 2, h / 2);
//	}
//	FloatRect getRect() {
//		return FloatRect(x, y, w, h);
//	}
//};
