#pragma once
#include "classGlobal.h"

class Player :public Entity { // класс Игрока
public:
	FloatRect rect;
	float x1, y1 = 0;
	float damage = 20.0;
	float reload_time = 0.1f;
	int dir = 0;
	int quest = 0;
	String File;
	Image image;
	bool reload = true;
	int gun = 0;
	enum { pistol, uzi, shotgun, machinegun } weapoon;
	bool take_uzi = false;
	bool take_shotgun = false;
	bool take_machinegun = false;
	bool take_bucket = false;

	float damage_pistol = 10;
	float damage_uzi = 15;
	float damage_shotgun = 5;
	float damage_machinegun = 20;
	float bonus_damage = 0;

	int ammo_uzi = 25;
	int ammo_shootgun = 8;
	int ammo_machinegun = 100;
	int ammo = 0;

	int choose_gun = 1;

	Player(String F, String Name, Level &lev, float X, float Y, float W, float H, int health_point) :Entity(image, Name, X, Y, W, H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		obj = lev.GetAllObjects();

		properties.health = health_point;
		File = F;//имя файла+расширение
		properties.w = W; properties.h = H;//высота и ширина
		image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture->loadFromImage(image);//закидываем наше изображение в текстуру
		sprite->setTexture(*texture);//заливаем спрайт текстурой
		pos.xy.x = X; pos.xy.y = Y;//координата появления спрайта
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h)));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
		weapoon = pistol;
	}

	void _chose_gun();

	void _take_gun();


	void _set_speed();

	void update(float time);

	FloatRect getRect();

	FloatRect getRect1();

	float getX();
	float getY();



	bool _map_event(float y1, float x1);

	void _quest_progress(float y1, float x1);

};