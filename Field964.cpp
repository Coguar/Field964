// Field964.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "map.h"
#include "cam.h"
#include "health.h"
#include "control.h"
//#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "GameMath.h"
#include "GoToTarget.h"
#include "GamesStruct.h"
#include "MenuStruct.h"
#include "Menu.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "action.h"
#include "Initiation.h"


using namespace sf;


void DrawingGame(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, float time)
{
	game.window->setView(*game.view1);
	game.window->clear(Color(55, 83, 10));
	game.lvl->Draw(*game.window);

	hero.player->update(time, *game.wallsChecker, game.sound->step, game.sound->dead, game.sound->win);

	for (auto puddle : lists.bloods) {
		game.window->draw(*puddle->s_blood);
	}

	for (std::shared_ptr<Slime> spite : lists.spites) {
		game.window->draw(*spite->sprite);
	}
	for (std::shared_ptr<Bonus> bon : lists.bonuses) {
		game.window->draw(*bon->sprite);
	}

	for (std::shared_ptr<Enemy> enemy: lists.entities) {
			game.window->draw(*enemy->sprite);
	}


	for (std::shared_ptr<Bullet> bull  : lists.bullets ) {
		bull->update(time, *game.wallsChecker);
		game.window->draw(*bull->sprite);
	}
	game.window->draw(*hero.player->sprite);
	for (std::shared_ptr<Tree> plant : lists.woods) {
		game.window->draw(*plant->sprite);
	}
	ShowHealth(*game.window, *info.text, hero.player->properties.health, *game.view1);
	ShowAmmo(*game.window, *info.text, hero.player->ammo, *game.view1);

	if (!hero.player->properties.life || hero.player->quest == Player::quest_status::finish) {
		game.is_end = true;
		FinishGameInit(config, game, hero.player->properties.life);
		game.finish_sprite->setPosition(game.view1->getCenter().x, game.view1->getCenter().y);
		game.window->draw(*game.finish_sprite);
		
	}
	game.aim_sprite->setPosition(game.pos);
	game.window->draw(*game.aim_sprite);

	game.window->display();
}

void gameProcces(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, Shoot & shoot, Monster & enemy, menuBools & menu_bool, MenuImg & menu_img) {
	while (game.window->pollEvent(game.event)) {
		if (game.event.type == sf::Event::Closed) {
			game.window->close();
		}

		if (game.event.type == Event::KeyReleased && game.event.key.code == Keyboard::Escape) {
			menu_bool.menu = !menu_bool.menu;
			menu_bool.change_music = true;
		}
		if (!menu_bool.menu && !game.is_end) {
			hero.player->sprite->setRotation(actionGetRotation(game.pos.x, game.pos.y, hero.player->pos.xy.x, hero.player->pos.xy.y) + 90);
			if (game.event.type == Event::MouseButtonPressed) {
				if (game.event.key.code == Mouse::Left) {
					game.reload_time = game.reload_clock.getElapsedTime().asSeconds();
					if (!hero.player->auto_gun) {
						actionShoot(lists, hero, shoot, config, game, game.reload_time, game.pos);
					}
					else {
						hero.player->spray = true;
					}
				}
			}
			if (hero.player->spray) {
				game.reload_time = game.reload_clock.getElapsedTime().asSeconds();
				actionShoot(lists, hero, shoot, config, game, game.reload_time, game.pos);
			}
			if (game.event.type == Event::MouseButtonReleased) {
				if (game.event.key.code == Mouse::Left) {
					hero.player->spray = false;
				}
			}
			if (game.event.type == Event::MouseWheelMoved) {
				if (game.event.mouseWheel.delta == 1) {
					hero.player->choose_gun = 1;
					if (hero.player->gun < hero.player->m_Guns.size() - 1) {
						hero.player->gun += 1;
					}
					else {
						hero.player->gun = 0;
					}
				}
				if (game.event.mouseWheel.delta == -1) {
					hero.player->choose_gun = -1;
					if (hero.player->gun > 0) {
						hero.player->gun -= 1;
					}
					else {
						hero.player->gun = hero.player->m_Guns.size() - 1;
					}
				}
			}
		}
	}

	if (!menu_bool.menu) {
		if (hero.player->properties.life == true) {
			controlPlayer(*hero.player->sprite, hero.player->dir, hero.player->properties.speed, game.time, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S);
		}
		eventTheyFollowYou(game, config, shoot, hero, lists);
		eventGetBonus(lists, hero, game.time, game);
		eventZombiesWave(hero, game, config, lists, enemy);
		eventZombieStopHero(lists, hero);
		eventBurningAcid(lists, hero, game.time);
		eventBulletDestroy(config, lists, hero, game);
		eventPuddleDestroy(lists);
		getCoord(hero.player->pos.xy.x, hero.player->pos.xy.y, *game.view1, *menu_img.sprite);
		eventDropBonus(lists, hero, game, config);
		DrawingGame(config, game, hero, lists, info, game.time);
	}
}

void main_game(Config & config, Game1 & game, Hero & hero, std::shared_ptr<Lists> & lists, Info & info, Shoot & shoot, Monster & enemy) {
	GameInit(config, game, hero);
	game.sound->music.play();

	MenuText menu_text;
	MissionText mission_text;
	MenuInfo menu_info;
	MenuConfig menu_config;
	menuBools menu_bool;
	std::shared_ptr<MenuImg> menu_img = std::make_shared<MenuImg>();

	initMenuFon(menu_config, *menu_img);
	initMenuText(menu_config, menu_info);

	game.sound->menu_music.play();


	while (game.window->isOpen()) {
		game.time = float(game.clock.getElapsedTime().asMicroseconds());
		game.reload_time = float(game.reload_clock.getElapsedTime().asMilliseconds());
		game.clock.restart();
		game.time = game.time / 10000;

		game.pixelPos = Mouse::getPosition(*game.window);
		game.pos = game.window->mapPixelToCoords(game.pixelPos);

		if (menu_bool.change_music) {
			menu_bool.change_music = false;
			if (menu_bool.menu) {
				game.sound->menu_music.play();
				game.sound->music.stop();
			}
			else {
				game.sound->menu_music.stop();
				game.sound->music.play();
			}
		}

		if (game.is_end) {
			game.sound->step.stop();
			menu_bool.first_play = true;
			game.time = 0;
		}

		if (menu_bool.menu) {

			while (game.window->pollEvent(game.event)) {
				if (game.event.type == sf::Event::Closed || menu_bool.exit) {
					game.window->close();
				}

				if (!menu_bool.first_play && game.event.type == Event::KeyReleased && game.event.key.code == Keyboard::Escape) {
					menu_bool.menu = !menu_bool.menu;
					menu_bool.change_music = true;
				}
				if (game.event.type == Event::MouseButtonPressed) {
					if (game.event.key.code == Mouse::Left) {
						clickedButton(menu_bool, menu_text, game.pos);
					}
				}
			}

			game.time = 0;

			showMenu(game, menu_text, *menu_info.text, *menu_img, menu_bool);
			showMission(game, mission_text, *menu_info.text, hero, *menu_img, menu_bool);
		}
		else {
			gameProcces(config, game, hero, *lists, info, shoot, enemy, menu_bool, *menu_img);
		}

		if (menu_bool.restart) {
			lists.reset();
			lists = std::make_shared<Lists>();
			eventPushLists(config, *lists, game, enemy);
			GameReInit(config, game, hero);
			menu_bool.menu = false;
			menu_bool.restart = false;
			menu_bool.first_play = false;

		}
	}
}

int main() {

		Config config;
		std::shared_ptr<Game1> game = std::make_shared<Game1>();
		std::shared_ptr<Hero> hero = std::make_shared<Hero>();
		Info info;
		std::shared_ptr<Lists> lists;// = std::make_shared<Lists>();
		std::shared_ptr<Monster> enemy = std::make_shared<Monster>();
		std::shared_ptr<Shoot> shoot = std::make_shared<Shoot>();

		InfoInit(config, info);
		main_game(config, *game, *hero, lists, info, *shoot, *enemy);
		return 0;
	}