#pragma once
#include "classGlobal.h"

class Enemy :public Entity {
public:
	FloatRect rect;
	bool player_contact = false;
	bool contact = false;
	float target_x, target_y, x1, y1 = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	float Xdir, Ydir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Enemy(String F, Level &lvl, float X, float Y, float W, float H, String bot_name) :Entity(image, bot_name, X, Y, W, H) {
		obj = lvl.GetAllObjects();
		if (bot_name == "normal") {
			properties.health = 100;
			properties.speed = 0.1f;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 71, 71));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
		}
		else if (bot_name == "boss") {
			properties.health = 950;
			properties.speed = 0.09f;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.xy.x = X; pos.xy.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.xy.x, pos.xy.y);
		}

	}
	void update(float time);

	FloatRect getRect();


	FloatRect getRect1();

	bool map_event(float y1, float x1);


	float getX();
	float getY();
};