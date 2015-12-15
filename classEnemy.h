#pragma once
#include "classGlobal.h"

class Enemy :public Entity {
public:
	FloatRect rect;
	bool player_contact = false;
	bool contact = false;
	float target_x, target_y, x1, y1 = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	float Xdir, Ydir = 0; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	Enemy(String F, Level &lvl, float X, float Y, float W, float H, String bot_name) :Entity(image, bot_name, X, Y, W, H) {
		obj = lvl.GetAllObjects();
		if (bot_name == "normal") {
			properties.health = 100;
			properties.speed = 0.1f;
			File = F;//��� �����+����������
			properties.w = W; properties.h = H;//������ � ������
			image.loadFromFile(File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
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
			File = F;//��� �����+����������
			properties.w = W; properties.h = H;//������ � ������
			image.loadFromFile(File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
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