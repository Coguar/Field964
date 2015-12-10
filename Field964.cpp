// Field964.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
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
//#include <list>
#include "Game_window.h"
#include "distantion.h"
#include "GoToTarget.h"
#include "sprite_position.h"
//#include "global.h"
//#include "level.h"
//#include "Classes.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "action.h"


using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

sf::View view1, view2;

void GameInit(Config & config, Game1 & game, Hero & hero)
{
	game.window = new RenderWindow(sf::VideoMode(800, 600), "Game");
	game.lvl = new Level;
	game.lvl->LoadFromFile(config.map);

	//hero->player_obj = new Object;
	hero.player_obj = game.lvl->GetObject("player1");

	hero.player = new Player(config.imageHeroPistol, hero.name, *game.lvl, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);

	game.view1 = new View;
	game.view1->setSize(800, 600);

}

void InfoInit(Config & config, Info & info) 
{
	info.font.loadFromFile(config.font);
	info.text = new Text("", info.font, info.font_size);
	info.text->setColor(Color::Red);
	info.text->setStyle(Text::Bold);
}

void GetTrees(Config & config, Lists * lists, Game1 & game)
{
	std::vector<Object> e = game.lvl->GetObjects("tree");
	for (int i = 0; i < e.size(); i++) {
		lists->woods.push_back(new Tree(config.Tree, e[i].rect.left, e[i].rect.top));
	}
}

void GetGuns(Config & config, Lists * lists, Game1 & game)
{
	std::vector<Object> e = game.lvl->GetObjects("uzi");
	for (int i = 0; i < e.size(); i++) {
		lists->bonuses.push_back(new Bonus(config.bonus, 4, e[i].rect.left, e[i].rect.top));
	}
	e = game.lvl->GetObjects("shotgun");
	for (int i = 0; i < e.size(); i++) {
		lists->bonuses.push_back(new Bonus(config.bonus, 5, e[i].rect.left, e[i].rect.top));
	}
	e = game.lvl->GetObjects("machinegun");
	for (int i = 0; i < e.size(); i++) {
		lists->bonuses.push_back(new Bonus(config.bonus, 6, e[i].rect.left, e[i].rect.top));
	}
}

void GetEnemys(Config & config, Lists * lists, Game1 & game, Monster & enemy)
{
	std::vector<Object> e = game.lvl->GetObjects("normal");
	String name;
	for (int i = 0; i < e.size(); i++) {

		switch (random_number(10)) {
		case 0: name  = config.zombie1;   break;
		case 1: name = config.zombie2;   break;
		case 2: name = config.zombie3;   break;
		case 3: name = config.zombie4;   break;
		case 4: name = config.zombie5;   break;
		case 5: name = config.zombie6;   break;
		case 6: name = config.zombie7;   break;
		case 7: name = config.zombie8;   break;
		case 8: name = config.zombie9;   break;
		case 9: name = config.zombie10;   break;
		}
		enemy.normal = new Enemy(name, *game.lvl, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal");

		lists->entities.push_back(enemy.normal);
	}
	e = game.lvl->GetObjects("boss");
	name = config.boss;
	for (int i = 0; i < e.size(); i++) {
		enemy.boss = new Enemy(name, *game.lvl, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");

		lists->entities.push_back(enemy.boss);
	}

}

void DrawingGame(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, float time)
{
	game.window->setView(*game.view1);
	game.window->clear(Color(55, 83, 10));
	game.lvl->Draw(*game.window);

	hero.player->update(time);

	for (lists.bon = lists.bonuses.begin(); lists.bon != lists.bonuses.end();lists.bon++) {
		game.window->draw(*(*lists.bon)->sprite);
	}

	for (lists.it = lists.entities.begin(); lists.it != lists.entities.end(); lists.it++) {
			game.window->draw(*(*lists.it)->sprite);
	}


	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); ) {
		(*lists.bull)->update(time);
		game.window->draw(*(*lists.bull)->sprite);
		lists.bull++;
	}
	game.window->draw(*hero.player->sprite);
	for (lists.wood = lists.woods.begin(); lists.wood != lists.woods.end(); lists.wood++) {
		game.window->draw(*(*lists.wood)->sprite);
	}
	ShowHealth(*game.window, *info.text, hero.player->health, *game.view1);
	ShowAmmo(*game.window, *info.text, hero.player->ammo, *game.view1);
	game.window->display();
}

void StartGame(Config & config, Game1 & game, Hero & hero, Lists * lists, Info & info, Shoot & shoot, Monster & enemy)
{
	Clock clock;
	Clock reload_clock;

	while (game.window->isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		float reload_time = reload_clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 10000;
		sf::Event event;

		Vector2i pixelPos = Mouse::getPosition(*game.window);
		Vector2f pos = game.window->mapPixelToCoords(pixelPos);

		hero.player->sprite->setRotation(actionGetRotation(pos.x, pos.y, hero.player->x, hero.player->y) + 90);
		while (game.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				game.window->close();
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					reload_time = reload_clock.getElapsedTime().asSeconds();
					//0
					actionShoot(lists, hero, shoot, config, game, reload_time, pos);
					reload_clock.restart();
				}
			}
			if (event.type == Event::MouseWheelMoved) {
				if (event.mouseWheel.delta == 1) {
					hero.player->choose_gun = 1;
					if (hero.player->gun < 3) {
						hero.player->gun += 1;
					}
					else {
						hero.player->gun = 0;
					}
				}
				if (event.mouseWheel.delta == -1) {
					hero.player->choose_gun = -1;
					if (hero.player->gun > 0) {
						hero.player->gun -= 1;
					}
					else {
						hero.player->gun = 3;
					}
				}
			}
		}


		if (hero.player->life == true) {
			controlPlayer(*hero.player->sprite, hero.player->dir, hero.player->speed, time, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S, 25);
		}
		for (lists->it = lists->entities.begin(); lists->it != lists->entities.end(); lists->it++) {
			gototarget((*lists->it)->Xdir, (*lists->it)->Ydir, hero.player->getX(), hero.player->getY(), (*lists->it)->getX(), (*lists->it)->getY());
			(*lists->it)->sprite->setRotation(actionGetRotation(hero.player->x, hero.player->y, (*lists->it)->x, (*lists->it)->y) + 90);

			eventZombieHustle(lists, hero);
			eventHitZombie(lists, hero, time);


			actionSlowMotion(game, time);
			eventZombieAtack(lists, hero, time);
		}

		eventGetBonus(lists, hero, time, game.speed_game);
		if (lists->entities.size() == 0) {
			GetEnemys(config, lists, game, enemy);
		}
		eventBulletDestroy(lists, hero, time);
		getCoord(hero.player->x, hero.player->y, *game.view1);
		eventDropBonus(lists, hero, time, config);
		DrawingGame(config, game, hero, *lists, info, time);
	}
}


int main() {

		Config config;
		Game1 * game = new Game1();
		Hero * hero = new Hero();
		Info info;
		Lists* lists = new Lists();
		Monster * enemy = new Monster();
		Shoot* shoot = new Shoot();

		GameInit(config, *game, *hero);
		InfoInit(config, info);
		GetEnemys(config, lists, *game, *enemy);
		GetTrees(config, lists, *game);
		GetGuns(config, lists, *game);

		float CurrentFrame = 0;
		float CurrentFrame1 = 0;
		float res = 0;

		bool hit;

		StartGame(config, *game, *hero, lists, info, *shoot, *enemy);
		return 0;
	}