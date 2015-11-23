#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "level.h"


class Entity {
public:
	std::vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life;
	sf:: Texture texture;
	sf::Sprite sprite;
	sf::String name;
	Entity(sf::Image &image, sf::String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setOrigin(w / 2, h / 2);
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(x + 10, y, h - 20, w - 10);
	}
};

class Enemy :public Entity {
public:
	FloatRect rect;
	bool player_contact = false;
	float target_x, target_y, x1, y1 = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int Xdir, Ydir = 0; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	Enemy(String F, Level &lvl, float X, float Y, float W, float H, String bot_name) :Entity(image, bot_name, X, Y, W, H) {
		obj = lvl.GetAllObjects();
		if (bot_name == "normal") {
			health = 100;
			speed = 0.01;
			File = F;//��� �����+����������
			w = W; h = H;//������ � ������
			image.loadFromFile(File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
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
			switch (Xdir) {//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
			case 0: dx = speed;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
			case 1: dx = -speed;  break;
			case 2: dx = 0;  break;
			}
			switch (Ydir) {//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
			case 0: dy = speed;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
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
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
			if (FloatRect(x1, y1, h, w).intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid") {
					wall = 1;
					printf("+");
				}
				return wall;
			}
	}

	float getX() {	//���� ������� ����� �������� ���������� �	
		return x;
	}
	float getY() {	//���� ������� ����� �������� ���������� Y 	
		return y;
	}
};

class Player :public Entity { // ����� ������
public:
	FloatRect rect;
	float x1, y1 = 0;
	float reload_time = 0.5;//���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	bool reload = true;

	Player(String F, String Name, Level &lev, float X, float Y, float W, float H, int health_point) :Entity(image, Name, X, Y, W, H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		obj = lev.GetAllObjects();
		health = health_point;
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile(File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(13, 9, w, h));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
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

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����
	Image image;
	Bullet(String F, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		image.loadFromFile(F);
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.3;
		w = h = 16;
		life = true;
		//���� ������������� � ������������
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

		x += dx*time;//���� �������� ���� �� �
		y += dy*time;//�� �

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
			if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			{
				life = false;// �� ���� �������
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	}

	FloatRect getRect() {
		return FloatRect(x, y, h, w);
	}
};

struct Game {
	RenderWindow* window;
	Clock clock;
	Clock reload_clock;


	std::list<Enemy*>  entities;//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<Enemy*>::iterator & it;//�������� ����� ��������� �� ��-��� ������

	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator& bull;
	Font  font;
	Text  text;
	Level  lvl;
	Image  BulletImage;
	Music  music;

	Object  player1;
	Object  player2;
	Object  normal_enemy;

	Player  human;
	Player  human1;

	float CurrentFrame = 0;
	float CurrentFrame1 = 0;
	float res = 0;

	bool hit;

};