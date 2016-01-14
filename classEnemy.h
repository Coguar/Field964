#pragma once
#include "classGlobal.h"

class Enemy :public Entity {
public:
	FloatRect rect;
	float recovery_spittle;
	float recovery_time = 1000;
	bool player_contact = false;
	bool contact = false;
	bool shooting = false;

	const float hit_time = 100;
	float hit_timer = 0;
	bool hit = false;
	int damage;

	bool angry;

	Vector2f target_xy;; 
	Vector2f xy1;
	Vector2f dir;
	String File; //файл с расширением
	String Name;
	Image image;//сфмл изображение
	Enemy(String F, float X, float Y, float W, float H, String bot_name) :Entity(bot_name, X, Y, W, H) {
		Name = bot_name;
		angry = false;
		if (bot_name == "normal") {
			properties.health = 100;
			properties.speed = 1.1f;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 71, 71));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
			damage = 10;
		}
		else if (bot_name == "boss") {
			properties.health = 950;
			properties.speed = 1.0f;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
			damage = 50;
		}
		else if (bot_name == "spitter") {
			properties.health = 350;
			properties.speed = 1.0f;
			recovery_spittle = 0;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
			damage = 5;
		}
		else if (bot_name == "box") {
			properties.health = 20;
			properties.speed = 0;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			//sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
			damage = 0;
		}

	}
	void _check_spit(float time, float p_pos_x, float p_pos_y);
	void _is_hit(float time);
	void update(float time, CollisionChecker & checker, float p_pos_x, float p_pos_y);

	FloatRect getRect();


	FloatRect getRect1();

	bool map_event(float y1, float x1);


	float getX();
	float getY();
};