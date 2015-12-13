#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "level.h"
#include <map>
#include <memory>

using namespace sf;

struct PositionObj
{
	float dx;
	float dy;

	float x;
	float y;

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
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	Entity(sf::Image & image, sf::String Name, float X, float Y, float W, float H) {
		pos.x = X; pos.y = Y; properties.w = W; properties.h = H; properties.name = Name; properties.moveTimer = 0;
		properties.speed = 0; properties.health = 100; pos.dx = 0; pos.dy = 0;
		properties.life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(properties.w / 2, properties.h / 2);
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(pos.x - properties.w / 2, pos.y - properties.h / 2, properties.h, properties.w);
	}
};

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
			pos.x = X; pos.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 71 , 71));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.x, pos.y);
		}
		else if (bot_name == "boss") {
			properties.health = 950;
			properties.speed = 0.09f;
			File = F;//имя файла+расширение
			properties.w = W; properties.h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			pos.x = X; pos.y = Y;
			sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(properties.w / 2, properties.h / 2);
			sprite->setPosition(pos.x, pos.y);
		}

	}
	void update(float time) {
		x1 = pos.x;
		y1 = pos.y;
		if (properties.health <= 0) {
			properties.life = false;
		}
		if (properties.life == true) {
			x1 += Xdir * time;
			
			if (map_event(pos.y, x1) == false && player_contact == false && contact == false) {
				pos.x = x1;
			}
			y1 += Ydir * time;
			if (map_event(y1, pos.x) == false && player_contact == false && contact == false) {
				pos.y = y1;
			}

			if (player_contact == true) {
				sprite->setColor(Color::Red);
			}
			else {
				sprite->setColor(Color::White);
			}

			sprite->setPosition(pos.x, pos.y);
		}
	}

	FloatRect getRect() {
		return FloatRect(pos.x - properties.w / 2, pos.y - properties.h / 2, properties.w, properties.h);
	}


	FloatRect getRect1() {
		return FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.w, properties.h);
	}

	bool map_event(float y1, float x1) {
		bool wall = 0;
		for (size_t i = 0; i < obj.size(); i++)//проходимся по объектам
			if (FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.h, properties.w).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid") {
					wall = true;
				}
			}
		return wall;
	}

	float getX() {	//этим методом будем забирать координату Х	
		return pos.x;
	}
	float getY() {	//этим методом будем забирать координату Y 	
		return pos.y;
	}
};

class Player :public Entity { // класс Игрока
public:
	FloatRect rect;
	float x1, y1 = 0;
	float damage = 20.0;
	float reload_time = 0.1f;//координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	bool reload = true;
	enum {pistol, uzi, shotgun, machinegun} weapoon;
	int gun = 0;

	bool take_uzi = false;
	bool take_shotgun = false;
	bool take_machinegun = false;

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
		pos.x = X; pos.y = Y;//координата появления спрайта
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h)));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
		weapoon = pistol;
	}

	void _chose_gun() {
		bool set_gun = false;
		while (set_gun == false) {
			switch (gun) {
			case 0: weapoon = pistol; set_gun = true;  break;
			case 1: weapoon = uzi;  if (take_uzi == false) { gun += choose_gun; } 
					else {set_gun = true;}
					break;
			case 2: weapoon = shotgun; if (take_shotgun == false) { gun += choose_gun; }
					else { set_gun = true; }
					break;
			case 3: weapoon = machinegun; if (take_machinegun == false) { gun += choose_gun; if (choose_gun == 1) { gun = 0; } }
					else { set_gun = true; }
					break;
			}
		}
	}

	void _take_gun() {
		switch (weapoon) {
		case pistol: image.loadFromFile("./files/sprites/player_pistol.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
			damage = damage_pistol + bonus_damage;  ammo = -1; break;
		case uzi: if (take_uzi == true) {
			image.loadFromFile("./files/sprites/player_uzi.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
		}
				  damage = damage_uzi + bonus_damage; ammo = ammo_uzi;  break;
		case shotgun:if (take_shotgun == true) {
			image.loadFromFile("./files/sprites/player_shotgun.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
		}
					 damage = damage_shotgun + bonus_damage; ammo = ammo_shootgun;  break;
		case machinegun: if (take_machinegun == true) {
			image.loadFromFile("./files/sprites/player_machinegun.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
		}
						 damage = damage_machinegun + bonus_damage; ammo = ammo_machinegun;  break;
		}
	}


	void _set_speed() {
		switch (dir) {
		case 0: pos.dx = properties.speed; pos.dy = 0;   break;
		case 1: pos.dx = -properties.speed; pos.dy = 0;   break;
		case 2: pos.dx = 0; pos.dy = properties.speed;   break;
		case 3: pos.dx = 0; pos.dy = -properties.speed;   break;
		case 4: pos.dx = float(properties.speed * 0.66); pos.dy = float(properties.speed * 0.66);   break;
		case 5: pos.dx = float(properties.speed * 0.66); pos.dy = float(-properties.speed * 0.66);   break;
		case 6: pos.dx = float(-properties.speed * 0.66); pos.dy = float(-properties.speed * 0.66);   break;
		case 7: pos.dx = float(-properties.speed * 0.66); pos.dy = float(properties.speed * 0.66);   break;
		}
	}

	void update(float time) {
		x1 = pos.x;
		y1 = pos.y;

		_chose_gun();
		_take_gun();
		_set_speed();

		x1 += pos.dx * time;
		y1 += pos.dy * time;

		if (_map_event(y1, x1) == false) {
			pos.x = x1;
			pos.y = y1;
		}

		properties.speed = 0;

		if (properties.health <= 0) {
			properties.life = false;
		}

		if (properties.life == false) {
			properties.health = 0;
		}
		sprite->setPosition(pos.x, pos.y);

	}

	FloatRect getRect() {
		return FloatRect(pos.x - properties.w / 2, pos.y - properties.h / 2, properties.h, properties.w);
		std::cout << properties.h << std::endl;
	}

	FloatRect getRect1() {
		return FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.h, properties.w);
	}

	float getX() {
		return pos.x;
	}
	float getY() {
		return pos.y;
	}



	bool _map_event(float y1, float x1) {
		bool wall = 0;
		for (size_t i = 0; i < obj.size(); i++)
			if (getRect1().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid") {
					wall = true;
				}
			}
		return wall;
	}
};

class Bullet {
public:
	std::vector<Object> obj;
	int direction;
	PositionObj pos;
	Properties properties;
	bool life;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	sf::String name;
	Image image;
	Bullet(String F, String Name, Level &lvl, float X, float Y, int W, int H, int dir) {
		image.loadFromFile(F);
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);

		obj = lvl.GetObjects("solid");
		pos.x = X;
		pos.y = Y;
		direction = dir;
		properties.speed = 3;
		properties.w = properties.h = 5;
		life = true;
	}


	void update(float time)
	{

		pos.x += pos.dx * time * 10;
		pos.y += pos.dy * time * 10;

		if (pos.x <= 0) pos.x = 1;
		if (pos.y <= 0) pos.y = 1;

		for (size_t i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}

		sprite->setPosition(pos.x + properties.w / 2, pos.y + properties.h / 2);
	}

	FloatRect getRect() {
		return FloatRect(pos.x, pos.y, properties.h, properties.w);
	}
};

class Bonus {
private:
	std::map<int, IntRect> bonus_rect =
	{ { 1, IntRect(0, 0, 32, 32) },
		{ 2, IntRect(32, 0, 32, 32) },
		{ 3, IntRect(64, 0, 32, 32) },
		{ 4, IntRect(0, 32, 32, 32) },
		{ 5, IntRect(32, 32, 128, 32) },
		{ 6, IntRect(0, 64, 128, 64) } };
public:
	int Name;
	PositionObj pos;
	Properties properties;

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	sf::String name;
	Image image;
	Bonus(String F, int name1, float X, float Y) {
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		pos.x = X;
		pos.y = Y;
		Name = name1;
		sprite->setTextureRect(bonus_rect[name1]);
		sprite->setPosition(pos.x, pos.y);
		sprite->setOrigin(properties.w / 2, properties.h / 2);
	}
	FloatRect getRect() {
		return FloatRect(pos.x, pos.y, 32, 32);
	}
};

class Tree {
public:
	int Name;
	float x, y;
	float w = 512.0;
	float h = 512.0;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	sf::String name;
	Image image;
	Tree(String F, float X, float Y) {
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		x = X;
		y = Y;
		sprite->setPosition(x, y);
		sprite->setOrigin(w / 2, h / 2);
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
};

class Item {
public:
	std::string Name;
	bool activ;
	float x;
	float y;
	sf::String name;
	Image image;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	Item(String F, float X, float Y) {
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		x = X;
		y = Y;
		sprite->setPosition(x, y);
		activ = false;
	}
};
