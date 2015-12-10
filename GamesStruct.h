#pragma once
#include "stdafx.h"
#include <SFML/Audio.hpp>
#include "Classes.h"
#include <list>


static struct Config {
	std::string imageHeroPistol = "./files/sprites/player_pistol.png";
	std::string imageHeroUzi = "./files/sprites/player_uzi.png";
	std::string imageHeroShotgun = "./files/sprites/player_shotgun.png";
	std::string imageHeroMachinegun = "./files/sprites/player_machinegun.png";

	std::string imageHeroWarrior = "./files/img/heroWar.png";

	std::string zombie1 = "./files/sprites/citizenzombie1.png";
	std::string zombie2 = "./files/sprites/citizenzombie2.png";
	std::string zombie3 = "./files/sprites/citizenzombie3.png";
	std::string zombie4 = "./files/sprites/citizenzombie4.png";
	std::string zombie5 = "./files/sprites/citizenzombie5.png";
	std::string zombie6 = "./files/sprites/citizenzombie6.png";
	std::string zombie7 = "./files/sprites/citizenzombie7.png";
	std::string zombie8 = "./files/sprites/citizenzombie8.png";
	std::string zombie9 = "./files/sprites/citizenzombie9.png";
	std::string zombie10 = "./files/sprites/citizenzombie10.png";
	std::string boss = "./files/sprites/boss.png";
	
	std::string Tree = "./files/img/tree1.png";
	std::string Bullet = "./files/img/bullet1.png";
	std::string Shot = "./files/img/drob.png";
	std::string fon_music = "./files/music/fon.ogg";
	std::string map = "mappp.tmx";
	std::string font = "./files/fonts/CyrilicOld.ttf";
	std::string bonus = "./files/img/bonus/bonuses.png";
};

static struct Game1 //структура в GameStruct
{
	sf::RenderWindow *window;
	sf::View *view1;
	sf::View *view2;
	Level *lvl;
	float timer = 0;
	float speed_game = 1;

};


static struct Hero
{
	Player* player;
	Object player_obj = Object();
	std::string name = "Player1";
	float H = 71.0;
	float W = 50.0;
	int health = 150;
};

static struct Shoot {
	Bullet * bullet;
	float H = 20;
	float W = 20;
};

static struct Monster
{
	Enemy* normal;
	Object monster_obj= Object();
	std::vector<Object> e;
	float normal_H =71.0;
	float normal_W = 71.0;
	int normal_health = 150;

	Enemy* boss;
	float boss_H = 256.0;
	float boss_W = 256.0;
	int boss_health = 950;
};

static struct Info
{
	Font font;
	Text *text;
	int font_size = 20;
};

static struct sounds
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


static struct Lists
{
	std::list<Enemy*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Enemy*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::list<Enemy*>::iterator it2;

	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator bull;

	std::list<Bonus*> bonuses;
	std::list<Bonus*>::iterator bon;

	std::list<Tree*> woods;
	std::list<Tree*>::iterator wood;
};