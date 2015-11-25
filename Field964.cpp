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
#include "Classes.h"
#include "GamesStruct.h"



using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

sf::View view1, view2;

void GameInit(Config & config, Game1 & game, Hero & hero)
{
	game.window = new RenderWindow(sf::VideoMode(800, 600), "Game");
	game.lvl = new Level;
	game.lvl->LoadFromFile(config.map);

	//hero->player_obj = new Object;
	hero.player_obj = game.lvl->GetObject("player1");

	std::cout << "+";
	hero.player = new Player(config.imageHeroMage, hero.name, *game.lvl, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);

	game.view1 = new View;
	game.view1->setSize(480, 320);

}

void InfoInit(Config & config, Info & info) 
{
	info.font.loadFromFile(config.font);
	info.text = new Text("", info.font, info.font_size);
	info.text->setColor(Color::Red);
	info.text->setStyle(Text::Bold);
}

void GetEnemys(Config & config, Lists * lists, Game1 & game, Monster & enemy)
{
	std::vector<Object> e = game.lvl->GetObjects("normal");
	for (int i = 0; i < e.size(); i++) {
		enemy.normal = new Enemy(config.NormalEnemy, *game.lvl, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal");
		lists->entities.push_back(enemy.normal);
	}
}

void DrawingGame(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, float time)
{
	game.window->setView(*game.view1);
	game.window->clear(Color(55, 83, 10));
	game.lvl->Draw(*game.window);
	ShowHealth(*game.window, *info.text, hero.player->health, *game.view1);

	hero.player->update(time);
	for (lists.it = lists.entities.begin(); lists.it != lists.entities.end(); lists.it++) {
		(*lists.it)->update(time);
		game.window->draw(*(*lists.it)->sprite);
	}
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); ) {
		(*lists.bull)->update(time);
		if ((*lists.bull)->life == false) {
			lists.bull = lists.bullets.erase(lists.bull);
		}
		else {
			game.window->draw(*(*lists.bull)->sprite);
			lists.bull++;
		}
	}
	game.window->draw(*hero.player->sprite);
	game.window->display();
}

void StartGame(Config & config, Game1 & game, Hero & hero, Lists * lists, Info & info, Shoot & shoot)
{
	Clock clock;
	Clock reload_clock;

	while (game.window->isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		float reload_time = reload_clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;
		sf::Event event;
		while (game.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				game.window->close();
			}
		}
			if (hero.player->life == true) {
				controlPlayer(*hero.player->sprite, hero.player->dir, hero.player->speed, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, 25);
				if (event.key.code == Keyboard::RControl)
				{
					reload_time = reload_clock.getElapsedTime().asSeconds();
					if (reload_time >= hero.player->reload_time) {
						hero.player->reload = true;
					}
					if (hero.player->reload == true) {
						hero.player->reload = false;
						reload_clock.restart();
						shoot.bullet = new Bullet(config.Bullet, "Bullet", *game.lvl, hero.player->x, hero.player->y, 5, 5, hero.player->dir);
						std::cout << lists->bullets.size() << std::endl;
						lists->bullets.push_back(shoot.bullet);
						std::cout << lists->bullets.size() << std::endl;
					}
				}

			}
			for (lists->it = lists->entities.begin(); lists->it != lists->entities.end(); lists->it++) {
				gototarget((*lists->it)->Xdir, (*lists->it)->Ydir, hero.player->getX(), hero.player->getY(), (*lists->it)->getX(), (*lists->it)->getY());
				if ((*lists->it)->getRect().intersects(hero.player->getRect())) {
					(*lists->it)->health = (*lists->it)->health - 100;
				}
				for (lists->bull = lists->bullets.begin(); lists->bull != lists->bullets.end();) {
					if ((*lists->it)->getRect().intersects((*lists->bull)->getRect())) {
						(*lists->it)->health = (*lists->it)->health - 20;
						lists->bull = lists->bullets.erase(lists->bull);
					}

					else {
						lists->bull++;
					}
				}
				if ((*lists->it)->getRect().intersects(hero.player->getRect())) {
					(*lists->it)->player_contact = true;
					if (int(time) % 10 == 0) {
						hero.player->health = hero.player->health - 0;
					}

				}
				else {
					(*lists->it)->player_contact = false;
				}
			}
		getCoord(hero.player->x, hero.player->y, *game.view1);
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

		float CurrentFrame = 0;
		float CurrentFrame1 = 0;
		float res = 0;

		bool hit;

		StartGame(config, *game, *hero, lists, info, *shoot);
		return 0;
	}