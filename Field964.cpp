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
#include "randomValue.h"
//#include "gameEvent.h"


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
	//есть
	for (lists.bon = lists.bonuses.begin(); lists.bon != lists.bonuses.end();lists.bon++) {
		game.window->draw(*(*lists.bon)->sprite);
		/*if ((*lists.bon)->getRect().intersects(hero.player->getRect())) {
			lists.bon = lists.bonuses.erase(lists.bon);
			//hero.player->health += 10;
		}
		else {
			lists.bon++;
		}*/
	}
	//есть функция 
	for (lists.it = lists.entities.begin(); lists.it != lists.entities.end();) {
		(*lists.it)->update(time * game.speed_game);
		if ((*lists.it)->life == false) {
			if (random_number(2) + 1 == 1) {
				lists.bonuses.push_back(new Bonus(config.bonus, random_number(3) + 1, (*lists.it)->x, (*lists.it)->y));
			}
			lists.it = lists.entities.erase(lists.it);
		}
		else{
			game.window->draw(*(*lists.it)->sprite);
			lists.it++;
		}
	}
	//----

	//есть функция
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); ) {
		(*lists.bull)->update(time * game.speed_game);
		if ((*lists.bull)->life == false) {
			lists.bull = lists.bullets.erase(lists.bull);
		}
		else {
			game.window->draw(*(*lists.bull)->sprite);
			lists.bull++;
		}
	}
	game.window->draw(*hero.player->sprite);
	for (lists.wood = lists.woods.begin(); lists.wood != lists.woods.end(); lists.wood++) {
		game.window->draw(*(*lists.wood)->sprite);
	}
	ShowHealth(*game.window, *info.text, hero.player->health, *game.view1);
	game.window->display();
}
//----------
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

		Vector2i pixelPos = Mouse::getPosition(*game.window);//забираем коорд курсора
		Vector2f pos = game.window->mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

															   // сделать функцию
		float dX = pos.x - hero.player->x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
		float dY = pos.y - hero.player->y;//он же, координата y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
															//std::cout << rotation << "\n";//смотрим на градусы в консольке
		hero.player->sprite->setRotation(rotation + 90);
		//

		while (game.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				game.window->close();
			}

			if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {
					reload_time = reload_clock.getElapsedTime().asSeconds();
					if (reload_time >= hero.player->reload_time) {
						hero.player->reload = true;
					}
					if (hero.player->reload == true) {
						hero.player->reload = false;
						reload_clock.restart();
						if (hero.player->weapoon != hero.player->shotgun) {
							shoot.bullet = new Bullet(config.Bullet, "Bullet", *game.lvl, hero.player->x, hero.player->y, 20, 20, hero.player->dir);
							std::cout << hero.player->y << std::endl;
							gototarget(shoot.bullet->dx, shoot.bullet->dy, pos.x, pos.y, hero.player->x, hero.player->y);
							shoot.bullet->sprite->setRotation(rotation);
							lists->bullets.push_back(shoot.bullet);
						}
						else {
							for (int i = 0; i < 7; i++) {
								shoot.bullet = new Bullet(config.Shot, "Bullet", *game.lvl, hero.player->x, hero.player->y, 10, 10, hero.player->dir);
								gototarget(shoot.bullet->dx, shoot.bullet->dy, pos.x - 20 + random_number(40) ,pos.y - 20 + random_number(40), hero.player->x, hero.player->y);
								lists->bullets.push_back(shoot.bullet);
							}
						}
					}
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
				dX = hero.player->x - (*lists->it)->x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
				dY = hero.player->y - (*lists->it)->y;//он же, координата y
				rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
																	
				(*lists->it)->sprite->setRotation(rotation + 90);
				//сделать функцию
				for (lists->it2 = lists->entities.begin(); lists->it2 != lists->entities.end(); lists->it2++) {
					if ((*lists->it2)->getRect() != (*lists->it)->getRect()) {
						if ((*lists->it2)->getRect().intersects((*lists->it)->getRect())) {
							if (calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists->it)->getX(), (*lists->it)->getY()) > calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists->it2)->getX(), (*lists->it2)->getY())) {
								(*lists->it)->x = (*lists->it)->x - (*lists->it)->Xdir;
								(*lists->it)->y = (*lists->it)->y - (*lists->it)->Ydir;
							}
							else {
								(*lists->it2)->x = (*lists->it2)->x - (*lists->it2)->Xdir;
								(*lists->it2)->y = (*lists->it2)->y - (*lists->it2)->Ydir;
							}
						}

					}
				}
				//function

				for (lists->bull = lists->bullets.begin(); lists->bull != lists->bullets.end();) {
					if ((*lists->it)->getRect().intersects((*lists->bull)->getRect())) {
						(*lists->it)->health = (*lists->it)->health - hero.player->damage;
						lists->bull = lists->bullets.erase(lists->bull);
					}

					else {
						lists->bull++;
					}
				}
				//******


				//timer
				if (game.speed_game != 1) {
					game.timer += time;
					if (game.timer >= 10000) {
						game.timer = 0;
						game.speed_game = 1;
					}
				}
				//****

				//DONE
				if ((*lists->it)->getRect().intersects(hero.player->getRect())) {
					(*lists->it)->player_contact = true;
					if (int(time) % 10 == 0) {
						hero.player->health = hero.player->health - 0;
					}

				}
				else {
					(*lists->it)->player_contact = false;
				}
				//**********
			}

			//bonus
			for (lists->bon = lists->bonuses.begin(); lists->bon != lists->bonuses.end();) {
				if ((*lists->bon)->getRect().intersects(hero.player->getRect())) {
					if ((*lists->bon)->Name == 1) {
						hero.player->damage += 10.0;
					}
					else if ((*lists->bon)->Name == 2) {
						hero.player->health += 10;
					}
					else if ((*lists->bon)->Name == 3) {
						game.speed_game = 0.1;
					}
					else if ((*lists->bon)->Name == 4) {
						hero.player->take_uzi = true;
					}
					else if ((*lists->bon)->Name == 5) {
						hero.player->take_shotgun = true;
					}
					else {
						hero.player->take_machinegun = true;
					}
					lists->bon = lists->bonuses.erase(lists->bon);
				}
				else {
					lists->bon++;
				}
			}
			//***

			if (lists->entities.size() == 0) {
				GetEnemys(config, lists, game, enemy);
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
		GetTrees(config, lists, *game);
		GetGuns(config, lists, *game);

		float CurrentFrame = 0;
		float CurrentFrame1 = 0;
		float res = 0;

		bool hit;

		StartGame(config, *game, *hero, lists, info, *shoot, *enemy);
		return 0;
	}