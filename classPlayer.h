#pragma once
#include "classGlobal.h"

#include <vector>

class Player :public Entity { // ����� ������
public:
	FloatRect rect;
	Vector2f xy1;
	float damage = 20.0;
	float reload_nonauto_time = 0.3f;
	float reload_auto_time = 0.1f;
	int dir = 0;

	bool contact = false;
	bool quest_move = false;
	bool spray = false;
	bool auto_gun;

	enum direction { left, right, up, down, u_left, u_right, d_left, d_right }step_to;
	std::map<int, direction> dir_variant = {
		{0, left},
		{ 1, right },
		{ 2, up },
		{ 3, down },
		{ 4, u_left },
		{ 5, u_right },
		{ 6, d_left },
		{ 7, d_right }
	};

	enum quest_status{start, find_car, find_gaz, find_busket, find_colon, go_to_car, finish}quest;
	String File;
	Image image;
	bool reload = true;
	enum weapoon { pistol, uzi, shotgun, machinegun }weapoons;
	bool take_bucket = false;

	std::vector<weapoon> m_Guns = { pistol };
	int gun = 0;

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

	Player(String F, String Name, float X, float Y, float W, float H, int health_point) :Entity(Name, X, Y, W, H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

		properties.health = health_point;
		File = F;//��� �����+����������
		properties.w = W; properties.h = H;//������ � ������
		properties.isGoing = false;
		image.loadFromFile(File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		texture->loadFromImage(image);//���������� ���� ����������� � ��������
		sprite->setTexture(*texture);//�������� ������ ���������
		pos.xy.x = X; pos.xy.y = Y;//���������� ��������� �������
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h)));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
		weapoons = pistol;
		quest = start;
	}

	void _chose_gun();

	void _take_gun();


	void _set_speed();

	void _do_sound(sf::Sound & sound);

	void _steps(sf::Sound & sound);

	void update(float time, CollisionChecker & checker, sf::Sound & sound, sf::Sound & dead_sound);

	FloatRect getRect();

	FloatRect getRect1();

	float getX();
	float getY();

	void _quest_progress(CollisionChecker & checker);

};