#pragma once
#include <SFML/Graphics.hpp>
#include "level.h"
#include <map>
#include <memory>
#include "classCollisionChecker.h"

using namespace sf;

struct PositionObj
{
	Vector2f dxy;
	Vector2f xy;

};

struct Properties
{
	float speed;
	float moveTimer;
	
	bool isGoing;

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
	Entity(sf::String Name, float X, float Y, float W, float H) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		pos.xy.x = X; pos.xy.y = Y; properties.w = W; properties.h = H; properties.name = Name; properties.moveTimer = 0;
		properties.speed = 0; properties.health = 100; pos.dxy.x = 0; pos.dxy.y = 0;
		properties.life = true;
		sprite->setOrigin(properties.w / 2, properties.h / 2);
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.h, properties.w);
	}
};