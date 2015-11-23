#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Classes.h"
#include <list>






struct Config {
	std::string imageHeroMage = "./files/img/heroMage.png";
	std::string imageHeroWarrior = "./files/img/heroWar.png";
	std::string NormalEnemy = "./files/img/EnemyNormal.png";
	std::string Bullet = "./files/img/bullet.png";
	std::string fon_music = "./files/music/fon.ogg";
	std::string map = "./files/maps/map.tmp";
	std::string font = "./files/fonts/CyrilicOld.ttf";
};

struct Game
{
	sf::RenderWindow *window;
	sf::View *view1;
	sf::View *view2;
	Level *lvl;

};


struct Hero 
{
	Player* player;
	Object player_obj;
	std::string name = "Player1";
	float H = 35.0;
	float W = 25.0;
	int health = 150;
};

struct Monster
{
	Enemy *normal;
	float normal_H = 35.0;
	float normal_W = 25.0;
	int normal_health = 150;
};

struct Info
{
	Font font;
	Text *text;
	int font_size = 20;
};

struct sounds
{
	sf::Music music;
	sf::SoundBuffer shootBuffer;
	sf::SoundBuffer hitBuffer;
	sf::SoundBuffer homeStepsBuffer;
	sf::SoundBuffer grassStepsBuffer;
	sf::SoundBuffer waterStepsBuffer;
	sf::SoundBuffer waveBuffer;
	sf::SoundBuffer deadBuffer;

};

struct Lists
{
	std::list<Enemy*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Enemy*>::iterator it;//итератор чтобы проходить по эл-там списка

	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator bull;
};