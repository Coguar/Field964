#pragma once
#include "classGlobal.h"

class Spitter :public Entity {
public:
	FloatRect rect;
	float recovery_spittle;
	float recovery_time = 10;
	bool can_spit = false;
	bool player_contact = false;
	bool contact = false;
	Vector2f target_xy;;
	Vector2f xy1;
	Vector2f dir;
	String File; 
	Image image;
	Spitter(String F, float X, float Y, float W, float H, String bot_name) :Entity(bot_name, X, Y, W, H) {
			properties.health = 350;
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
	void _check_spit(float time, float p_pos_x, float p_pos_y);
	void update(float time, CollisionChecker & checker, float p_pos_x, float p_pos_y);

	FloatRect getRect();


	FloatRect getRect1();


	float getX();
	float getY();
};