#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "level.h"

using namespace sf;

static class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life;
	sf:: Texture* texture = new Texture;
	sf::Sprite* sprite = new Sprite;
	sf::String name;
	Entity(sf::Image & image, sf::String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(w / 2, h / 2);
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(x - w / 2, y - h / 2, h, w);
	}
};

static class Enemy :public Entity {
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
			health = 100;
			speed = 0.1;
			File = F;//имя файла+расширение
			w = W; h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			x = X; y = Y;
			sprite->setTextureRect(IntRect(0, 0, 71 , 71));
			sprite->setOrigin(w / 2, h / 2);
			sprite->setPosition(x, y);
		}
		else if (bot_name == "boss") {
			health = 950;
			speed = 0.09;
			File = F;//имя файла+расширение
			w = W; h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture->loadFromImage(image);
			sprite->setTexture(*texture);
			x = X; y = Y;
			sprite->setTextureRect(IntRect(0, 0, 256, 256));
			sprite->setOrigin(w / 2, h / 2);
			sprite->setPosition(x, y);
		}

	}
	void update(float time) {
		x1 = x;
		y1 = y;
		if (health <= 0) {
			life = false;
		}
		if (life == true) {
			/*switch (Xdir) {//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			case 0: dx = speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case 1: dx = -speed;  break;
			case 2: dx = 0;  break;
			}
			switch (Ydir) {//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			case 0: dy = speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case 1: dy = -speed;  break;
			case 2: dy = 0;  break;
			}*/

			//spriteposition(*sprite, Xdir, Ydir, time);
			x1 += Xdir * time;
			
			if (map_event(y, x1) == false && player_contact == false && contact == false) {
				x = x1;
			}
			y1 += Ydir * time;
			if (map_event(y1, x) == false && player_contact == false && contact == false) {
				y = y1;
			}

			if (player_contact == true) {
				sprite->setColor(Color::Red);
			}
			else {
				sprite->setColor(Color::White);
			}

			sprite->setPosition(x, y);
		}
	}

	FloatRect getRect() {
		return FloatRect(x - w / 2, y - h / 2, w, h);
	}


	FloatRect getRect1() {
		return FloatRect(x1 - w / 2, y1 - h / 2, w, h);
	}

	bool map_event(float y1, float x1) {
		bool wall = 0;
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (FloatRect(x1 - w / 2, y1 - h / 2, h, w).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid") {
					wall = 1;
				}
				return wall;
			}
	}

	float getX() {	//этим методом будем забирать координату Х	
		return x;
	}
	float getY() {	//этим методом будем забирать координату Y 	
		return y;
	}
};

static class Player :public Entity { // класс Игрока
public:
	FloatRect rect;
	float x1, y1 = 0;
	float damage = 20.0;
	float reload_time = 0.1;//координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
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

		health = health_point;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture->loadFromImage(image);//закидываем наше изображение в текстуру
		sprite->setTexture(*texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite->setTextureRect(IntRect(8, 0, 50, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
		weapoon = pistol;
	}

	void update(float time) {
		x1 = x;
		y1 = y;


		switch (gun) {
		case 0: weapoon = pistol;  break;
		case 1: weapoon = uzi;  if (take_uzi == false) { gun += choose_gun; }  break;
		case 2: weapoon = shotgun; if (take_shotgun == false) { gun += choose_gun; }  break;
		case 3: weapoon = machinegun; if (take_machinegun == false) { gun += choose_gun; if (choose_gun == 1) { gun = 0; } }  break;
		}

		switch (weapoon) {
		case pistol: image.loadFromFile("./files/sprites/player_pistol.png"); texture->loadFromImage(image); 
			sprite->setTextureRect(IntRect(8, 0, 50, h)); sprite->setOrigin(w / 2, h / 2); 
			damage = damage_pistol + bonus_damage;  ammo = -1; break;
		case uzi: if (take_uzi == true) {
			image.loadFromFile("./files/sprites/player_uzi.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(8, 0, 50, h)); sprite->setOrigin(w / 2, h / 2);
		} 
			damage = damage_uzi + bonus_damage; ammo = ammo_uzi;  break;
		case shotgun:if (take_shotgun == true) {
			image.loadFromFile("./files/sprites/player_shotgun.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(w / 2 + 11, 100 / 2);
		} 
			damage = damage_shotgun + bonus_damage; ammo = ammo_shootgun;  break;
		case machinegun: if (take_machinegun == true) {
			image.loadFromFile("./files/sprites/player_machinegun.png"); texture->loadFromImage(image);
			sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(w / 2 + 11, 100 / 2);
		}
		damage = damage_machinegun + bonus_damage; ammo = ammo_machinegun;  break;
		}

		switch (dir) {
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		case 4: dx = speed * 0.66; dy = speed * 0.66;   break;
		case 5: dx = speed * 0.66; dy = -speed * 0.66;   break;
		case 6: dx = -speed * 0.66; dy = -speed * 0.66;   break;
		case 7: dx = -speed * 0.66; dy = speed * 0.66;   break;

		}
		x1 += dx*time;
		y1 += dy*time;

		if (map_event(y1, x1) == false) {
			x = x1;
			y = y1;
		}

		speed = 0;

		if (health <= 0) {
			life = false;
		}

		if (life == false) {
			//sprite->setTextureRect(IntRect(392, 11, w, h));
			health = 0;
		}
		sprite->setPosition(x, y);

	}

	FloatRect getRect() {
		return FloatRect(x - w / 2, y - h / 2, h, w);
		std::cout << h << std::endl;
	}

	FloatRect getRect1() {
		return FloatRect(x1 - w / 2, y1 - h / 2, h, w);
		std::cout << h << std::endl;
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}



	bool map_event(float y1, float x1) {
		bool wall = 0;
		for (int i = 0; i < obj.size(); i++)
			if (getRect1().intersects(obj[i].rect))
			{
				std::cout << obj[i].name;
				if (obj[i].name == "solid") {
					wall = true;
					std::cout << "Yes";
				}
				return wall;
			}
	}
};

static class Bullet {//класс пули
public:
	std::vector<Object> obj;
	int direction;//направление пули
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life;
	sf::Texture* texture = new Texture;
	sf::Sprite* sprite = new Sprite;
	sf::String name;
	Image image;
	Bullet(String F, String Name, Level &lvl, float X, float Y, int W, int H, int dir) {
		image.loadFromFile(F);
		std::cout << "nice";
		life = true;
		texture->loadFromImage(image);
		sprite->setTexture(*texture);

		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 3;
		w = h = 5;
		life = true;
		//выше инициализация в конструкторе
	}


	void update(float time)
	{
		/*switch (direction)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		case 4: dx = speed * 0.66; dy = speed * 0.66;   break;
		case 5: dx = speed * 0.66; dy = -speed * 0.66;   break;
		case 6: dx = -speed * 0.66; dy = -speed * 0.66;   break;
		case 7: dx = -speed * 0.66; dy = speed * 0.66;   break;
		}*/

		x += dx*time * 10;//само движение пули по х
		y += dy*time * 10;//по у

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}

		sprite->setPosition(x + w / 2, y + h / 2);//задается позицию пуле
	}

	FloatRect getRect() {
		return FloatRect(x, y, h, w);
	}
};

static class Bonus {
public:
	int Name;
	float x, y;
	int w, h;
	sf::Texture* texture = new Texture;
	sf::Sprite* sprite = new Sprite;
	sf::String name;
	Image image;
	Bonus(String F, int name1, float X, float Y) {
		image.loadFromFile(F);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		x = X;
		y = Y;
		Name = name1;
		switch (Name)
		{
		case 1: sprite->setTextureRect(IntRect(0, 0, 32, 32)); break;
		case 2: sprite->setTextureRect(IntRect(32 * (Name - 1), 0, 32, 32)); break;
		case 3: sprite->setTextureRect(IntRect(32 * (Name - 1), 0, 32, 32)); break;
		case 4: sprite->setTextureRect(IntRect(0, 32, 32, 32)); break;
		case 5: sprite->setTextureRect(IntRect(32 , 32, 128, 32)); break;
		case 6: sprite->setTextureRect(IntRect(0, 64, 128, 64)); break;
		}
		
		sprite->setPosition(x, y);
		sprite->setOrigin(w / 2, h / 2);
	}
	FloatRect getRect() {
		return FloatRect(x, y, 32, 32);
	}
};

static class Tree {
public:
	int Name;
	float x, y;
	float w = 512.0;
	float h = 512.0;
	sf::Texture* texture = new Texture;
	sf::Sprite* sprite = new Sprite;
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
