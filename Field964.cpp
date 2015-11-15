// Field964.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "cam.h"
#include "drawMap.h"
#include "health.h"
#include "control.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Game_window.h"
#include "distantion.h"
#include "GoToTarget.h"
#include "sprite_position.h"
#include "global.h"
#include "level.h"



using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

sf::View view1, view2;

class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect() {
		return FloatRect(x + 10, y, h - 20, w - 10);
	}
};

class Enemy :public Entity {
public:
	FloatRect rect;
	bool player_contact = false;
	float target_x, target_y, x1, y1 = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int Xdir, Ydir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Enemy(String F, Level &lvl, float X, float Y, float W, float H, String bot_name) :Entity(image, bot_name, X, Y, W, H) {
		obj = lvl.GetAllObjects();
		if (bot_name == "normal") {
			health = 100;
			speed = 0.01;
			File = F;//имя файла+расширение
			w = W; h = H;//высота и ширина
			image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			x = X; y = Y;
			sprite.setTextureRect(IntRect(13, 9, w, h));
			sprite.setPosition(x, y);
		}
	}
	void update(float time) {
		x1 = x;
		y1 = y;
		if (health <= 0) {
			life = false;
		}
		if (life == true) {
			switch (Xdir) {//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			case 0: dx = speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case 1: dx = -speed;  break;
			case 2: dx = 0;  break;
			}
			switch (Ydir) {//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			case 0: dy = speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case 1: dy = -speed;  break;
			case 2: dy = 0;  break;
			}
			spriteposition(sprite, Xdir, Ydir, time);
			x1 += dx * time;
			if (map_event(y, x1) == false && player_contact == false) {
				x = x1;
			}
			y1 += dy * time;
			if (map_event(y1, x) == false && player_contact == false) {
				y = y1;
			}

			if (player_contact == true) {
				sprite.setColor(Color::Red);
			}
			else {
				sprite.setColor(Color::White);
			}

			sprite.setPosition(x, y);
		}
	}

	FloatRect getRect() {
		return FloatRect(x, y, h, w);
	}


	FloatRect getRect1() {
		return FloatRect(x1, y1, h, w);
	}
	
	bool map_event(float y1, float x1) {
		bool wall = 0;
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (FloatRect(x1, y1, h, w).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid") {
					wall = 1;
					printf("+");
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

class Player :public Entity { // класс Игрока
public:
	FloatRect rect;
	float x1, y1 = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение

	Player(String F, String Name, Level &lev, float X, float Y, float W, float H, int health_point) :Entity(image, Name, X, Y, W, H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		obj = lev.GetAllObjects();
		health = health_point;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(13, 9, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	}

	void update(float time) {
		x1 = x;
		y1 = y;
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
			sprite.setTextureRect(IntRect(392, 11, w, h));
			health = 0;
		}
		sprite.setPosition(x, y - 15); 

	}

	FloatRect getRect() {
		return FloatRect(x + 10, y, h - 20, w - 10);
	}

	FloatRect getRect1() {
		return FloatRect(x1, y1, h - 20, w - 10);
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
				if (obj[i].name == "solid") {
					wall = true;
				}
				return wall;
			}
	}
};

class Bullet :public Entity {//класс пули
public:
	int direction;//направление пули

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.3;
		w = h = 16;
		life = true;
		//выше инициализация в конструкторе
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		case 4: dx = speed * 0.66; dy = speed * 0.66;   break;
		case 5: dx = speed * 0.66; dy = -speed * 0.66;   break;
		case 6: dx = -speed * 0.66; dy = -speed * 0.66;   break;
		case 7: dx = -speed * 0.66; dy = speed * 0.66;   break;
		}

		x += dx*time;//само движение пули по х
		y += dy*time;//по у

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
	}

	FloatRect getRect() {
		return FloatRect(x, y, h, w);
	}
};


int main(){

	std::list<Enemy*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Enemy*>::iterator it;//итератор чтобы проходить по эл-там списка

	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator bull;


	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	Image map_image;
	map_image.loadFromFile("tile.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);


	view2.setViewport(sf::FloatRect(0, 0, 0.499f, 1.0f));
	view1.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
	view1.setSize(320 , 480);
	view2.setSize(320, 480);

	RenderWindow window(sf::VideoMode(1280, 480), "Field");
	window.clear(Color::White);
	view1.reset(sf::FloatRect(0, 0, 512, 512));
	view2.reset(sf::FloatRect(0, 0, 512, 512));

	Level lvl;
	lvl.LoadFromFile("map.tmx");

	std::vector<Object> e = lvl.GetObjects("normal");
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy("3.png", lvl, e[i].rect.left, e[i].rect.top, 25.0, 35.0, "normal"));
	//Game_window game_window(window, H, W);


	Music music;
	music.openFromFile("fon2.ogg");
	music.setVolume(5);
	music.play();

	Object player1 = lvl.GetObject("player1");
	Object player2 = lvl.GetObject("player2");
	Object easyEnemyObject = lvl.GetObject("normal");

	Player p("1.png","Player1", lvl, player1.rect.left, player1.rect.top, 25.0, 35.0, 100);//player11.rect.left, player11.rect.top,
	Player p1("2.png","Player2", lvl, player2.rect.left, player2.rect.top, 25.0, 35.0, 250);
	//Enemy normal("3.png", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 25.0, 35.0, "normal");

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("ball1.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету

	float CurrentFrame = 0;
	float CurrentFrame1 = 0;
	float res = 0;
	
	bool hit;

	Clock clock;

	while (window.isOpen()){
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); 
		time = time / 800;
		sf::Event event;

	//////////////////////////////////////////Управление/////////////////////////////////////////
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (p.life == true) {
			controlPlayer(p.sprite, p.dir, p.speed, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, 25);
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::Space)
				{
					bullets.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 5, 5, p.dir));
				}
		}
			if (p1.life == true) {
				controlPlayer(p1.sprite, p1.dir, p1.speed, time, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S, 35);
				
				if (event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Q) {
						hit = true;
					}
				if (event.type == Event::KeyReleased)
					if (event.key.code == Keyboard::Q){
						hit = false;
					}
			}
			for (it = entities.begin(); it != entities.end(); ) {
				if ((*it)->getRect().intersects(p1.getRect()) ) {
					(*it)->health = (*it)->health - 100;
				}
				for (bull = bullets.begin(); bull != bullets.end();) {
					if ((*it)->getRect().intersects((*bull)->getRect())) {
						(*it)->health = (*it)->health - 20;
						bull = bullets.erase(bull);
					}

					else {
						bull++;
					}
				}

				if ((*it)->getRect().intersects(p.getRect())) {
					if (int(time) % 10 == 0) {
						p.health = p.health - 0;
					}
				}
				if ((*it)->getRect().intersects(p1.getRect())) {
					if (int(time) % 10 == 0) {
						p1.health = p1.health - 0;
					}
				}

				if (p.life == false && p1.life == true) {
					gototarget((*it)->Xdir, (*it)->Ydir, p1.getX(), p1.getY(), (*it)->getX(), (*it)->getY());
				}
				else if (p1.life == false && p.life == true) {
					gototarget((*it)->Xdir, (*it)->Ydir, p.getX(), p.getY(), (*it)->getX(), (*it)->getY());
				}
				else {
					if (calculateDistantion((*it)->getX(), (*it)->getY(), p.getX(), p.getY()) > calculateDistantion((*it)->getX(), (*it)->getY(), p1.getX(), p1.getY())) {
						gototarget((*it)->Xdir, (*it)->Ydir, p1.getX(), p1.getY(), (*it)->getX(), (*it)->getY());
					}
					else
					{
						gototarget((*it)->Xdir, (*it)->Ydir, p.getX(), p.getY(), (*it)->getX(), (*it)->getY());;
					}
				}

				if (((*it)->getRect().intersects(p.getRect()) && p.life == true) | ((*it)->getRect().intersects(p1.getRect()) && p1.life == true)) {
					(*it)->player_contact = true;

				}
				else {
					(*it)->player_contact = false;
				}

				if ((*it)->health < 1) {
					it = entities.erase(it);
				}
				else {
					it++;
				}
			}
		  


		getCoord(p.getX(), p.getY(), p1.getX(), p1.getY(), view1, view2);
		window.setView(view1);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);
		ShowHealth(window, text, p.health, view1);

		p.update(time);
		p1.update(time);
		for (it = entities.begin(); it != entities.end(); it++) {
			(*it)->update(time);
		}
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}
		for (bull = bullets.begin(); bull != bullets.end(); ) {
			(*bull)->update(time);
			if ((*bull)->life == false) {
				bull = bullets.erase(bull);
			}
			else {
				window.draw((*bull)->sprite);
				bull++;
			}
		}
		window.draw(p1.sprite);
		window.draw(p.sprite);

		window.setView(view2);
		lvl.Draw(window);
		ShowHealth(window, text, p1.health, view2);
		p1.update(time);
		p.update(time);
		for (it = entities.begin(); it != entities.end(); it++) {
			(*it)->update(time);
		}
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}

		for (bull = bullets.begin(); bull != bullets.end(); bull++) {
			window.draw((*bull)->sprite);
		}

		window.draw(p.sprite);
		window.draw(p1.sprite);

		window.display();
		window.clear();
	}

	return 0;
}