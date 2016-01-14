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
//#include <thread> 
//#include <chrono>

using namespace sf;

sf::View view1;

//void SoundInit(Config & config, Game1 & game) {
//	game.sound->music.openFromFile(config.fon);
//	game.sound->music.setLoop(true);
//	game.sound->music.setVolume(10);
//
//	game.sound->menu_music.openFromFile(config.menu);
//	game.sound->menu_music.setLoop(true);
//	//game.sound->menu_music.setVolume(10);
//
//	game.sound->step_buffer.loadFromFile(config.step_sound);
//	game.sound->step.setBuffer(game.sound->step_buffer);
//	game.sound->step.setLoop(true);
//
//	game.sound->wave_buffer.loadFromFile(config.wave_sound);
//	game.sound->wave.setBuffer(game.sound->wave_buffer);
//
//	game.sound->shoot_buffer.loadFromFile(config.shot_sound);
//	game.sound->shoot.setBuffer(game.sound->shoot_buffer);
//	game.sound->shoot.setVolume(5);
//
//	game.sound->uzi_buffer.loadFromFile(config.uzi);
//	game.sound->uzi.setBuffer(game.sound->uzi_buffer);
//	game.sound->uzi.setVolume(5);
//
//	game.sound->mgun_buffer.loadFromFile(config.mgun);
//	game.sound->mgun.setBuffer(game.sound->mgun_buffer);
//	game.sound->mgun.setVolume(5);
//
//	game.sound->shootgun_buffer.loadFromFile(config.shotgun_sound);
//	game.sound->shootgun.setBuffer(game.sound->shootgun_buffer);
//	game.sound->shootgun.setVolume(5);
//
//	game.sound->cock_buffer.loadFromFile(config.cock);
//	game.sound->cock.setBuffer(game.sound->cock_buffer);
//	game.sound->cock.setVolume(5);
//
//	game.sound->pickup_buffer.loadFromFile(config.pickup);
//	game.sound->pickup.setBuffer(game.sound->pickup_buffer);
//	game.sound->pickup.setVolume(10);
//
//	game.sound->move_buffer.loadFromFile(config.move);
//	game.sound->move.setBuffer(game.sound->move_buffer);
//	game.sound->move.setVolume(10);
//
//	game.sound->pain_buffer.loadFromFile(config.pain);
//	game.sound->pain.setBuffer(game.sound->pain_buffer);
//	game.sound->pain.setVolume(10);
//
//	game.sound->dead_buffer.loadFromFile(config.dead);
//	game.sound->dead.setBuffer(game.sound->dead_buffer);
//	game.sound->dead.setVolume(10);
//
//	game.sound->win_buffer.loadFromFile(config.win_sound);
//	game.sound->win.setBuffer(game.sound->win_buffer);
//	game.sound->win.setVolume(10);
//
//	game.sound->z_dead_buffer.loadFromFile(config.z_dead);
//	game.sound->z_dead.setBuffer(game.sound->z_dead_buffer);
//	game.sound->z_dead.setVolume(10);
//
//	game.sound->z_attack_buffer.loadFromFile(config.z_attack);
//	game.sound->z_attack.setBuffer(game.sound->z_attack_buffer);
//	game.sound->z_attack.setVolume(10);
//
//	game.sound->z_pain_buffer.loadFromFile(config.z_pain);
//	game.sound->z_pain.setBuffer(game.sound->z_pain_buffer);
//	game.sound->z_pain.setVolume(10);
//
//	game.sound->z_call_buffer.loadFromFile(config.z_call);
//	game.sound->z_call.setBuffer(game.sound->z_call_buffer);
//	game.sound->z_call.setVolume(10);
//
//	game.sound->zombie_hit_buffer.loadFromFile(config.zombie_hit);
//	game.sound->zombie_hit.setBuffer(game.sound->zombie_hit_buffer);
//	game.sound->zombie_hit.setVolume(10);
//
//}
//
//void GameInit(Config & config, Game1 & game, Hero & hero)
//{
//	game.is_end = false;
//
//	game.window = std::make_shared<RenderWindow>(sf::VideoMode(800, 600), "Game");
//	game.lvl = std::make_shared<Level>();
//	game.lvl->LoadFromFile(config.map);
//
//	game.sound = std::make_shared<sounds>();
//	SoundInit(config, game);
//	hero.player_obj = game.lvl->GetObject("player1");
//	game.wallsChecker = std::make_shared<CollisionChecker>(game.lvl);
//	hero.player = std::make_shared<Player>(config.imageHeroPistol, hero.name, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);
//
//	game.view1 = std::make_shared<View>();
//	game.view1->setSize(800, 600);
//
//}
//
//void GameReInit(Config & config, Game1 & game, Hero & hero)
//{
//	game.is_end = false;
//
//	hero.player_obj = game.lvl->GetObject("player1");
//	hero.player = std::make_shared<Player>(config.imageHeroPistol, hero.name, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);
//}
//
//void FinishGameInit(Config & config, Game1 & game, bool & life){
//	game.finish_texture = std::make_shared<Texture>();
//	game.finish_sprite = std::make_shared<Sprite>();
//	if (life) {
//		game.finish_texture->loadFromFile(config.win);
//	}
//	else {
//		game.finish_texture->loadFromFile(config.lose);
//	}
//	game.finish_sprite->setTexture(*game.finish_texture);
//	game.finish_sprite->setOrigin(game.finish_texture->getSize().x / 2, game.finish_texture->getSize().y / 2);
//}
//
//void InfoInit(Config & config, Info & info) 
//{
//	info.font.loadFromFile(config.font);
//	info.text = std::make_shared<Text>("", info.font, info.font_size);
//	info.text->setColor(Color::Red);
//	info.text->setStyle(Text::Bold);
//}

//void GetTrees(Config & config, Lists & lists, Game1 & game)
//{
//	std::vector<Object> e = game.lvl->GetObjects("tree");
//	for (size_t i = 0; i < e.size(); i++) {
//		lists.woods.push_back(std::make_shared<Tree>(config.Tree, e[i].rect.left, e[i].rect.top));
//	}
//}
//
//void GetGuns(Config & config, Lists & lists, Game1 & game)
//{
//	std::vector<Object> e = game.lvl->GetObjects("uzi");
//	for (size_t i = 0; i < e.size(); i++) {
//		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 7, e[i].rect.left, e[i].rect.top));
//	}
//	e = game.lvl->GetObjects("shotgun");
//	for (size_t i = 0; i < e.size(); i++) {
//		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 8, e[i].rect.left, e[i].rect.top));
//	}
//	e = game.lvl->GetObjects("machinegun");
//	for (size_t i = 0; i < e.size(); i++) {
//		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 9, e[i].rect.left, e[i].rect.top));
//	}
//	e = game.lvl->GetObjects("bucket");
//	for (size_t i = 0; i < e.size(); i++) {
//		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 10, e[i].rect.left, e[i].rect.top));
//	}
//}
//
//
//void GetEnemys(Config & config, Lists & lists, Game1 & game, Monster & enemy)
//{
//	std::vector<Object> e = game.lvl->GetObjects("box");
//	String name;
//	int number;
//
//	name = config.box;
//	for (size_t i = 0; i < e.size(); i++) {
//		//enemy.boss = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");
//
//		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.box_W, enemy.box_H, "box"));
//	}
//
//	e = game.lvl->GetObjects("normal");
//	for (size_t i = 0; i < e.size() - 1; i++) {
//		number = (random_number(10));
//		name = config.zombies[number];
//	//	enemy.normal = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal");
//		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal"));
//		//enemy.normal.reset();
//	}
//
//	e = game.lvl->GetObjects("spitter");
//	name = config.spitter;
//	for (size_t i = 0; i < e.size(); i++) {
//		//enemy.spitter = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter");
//
//		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter"));
//		enemy.spitter.reset();
//
//	}
//
//	e = game.lvl->GetObjects("boss");
//	name = config.boss;
//	for (size_t i = 0; i < e.size(); i++) {
//		//enemy.boss = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");
//
//		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss"));
//		enemy.boss.reset();
//	}
//
//
//
//}

void DrawingGame(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, float time)
{
	game.window->setView(*game.view1);
	game.window->clear(Color(55, 83, 10));
	game.lvl->Draw(*game.window);

	hero.player->update(time, *game.wallsChecker, game.sound->step, game.sound->dead);

	for (auto puddle : lists.bloods) {
		game.window->draw(*puddle->s_blood);
		std::cout << lists.bloods.size() << std::endl;
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
		game.finish_sprite->setPosition(hero.player->pos.xy);
		game.window->draw(*game.finish_sprite);
		
	}

	game.window->display();
}

void clearLists(Lists & lists) {
	lists.entities.clear();
	lists.bonuses.clear();
	lists.bullets.clear();
	lists.spites.clear();
	lists.spites.clear();
	lists.woods.clear();
}

void pushLists(Config & config, Lists & lists, Game1 & game, Monster & enemy) {
	eventGetEnemys(config, lists, game, enemy);
	eventGetTrees(config, lists, game);
	eventGetGuns(config, lists, game);
}

void gameProcces(Config & config, Game1 & game, Hero & hero, Lists & lists, Info & info, Shoot & shoot, Monster & enemy, menuBools & menu_bool, MenuImg & menu_img) {
	//hero.player->sprite->setRotation(actionGetRotation(game.pos.x, game.pos.y, hero.player->pos.xy.x, hero.player->pos.xy.y) + 90);
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
		for (lists.enemy = lists.entities.begin(); lists.enemy != lists.entities.end(); lists.enemy++) {
			if ((*lists.enemy)->angry) {
				gototarget((*lists.enemy)->dir.x, (*lists.enemy)->dir.y, hero.player->getX(), hero.player->getY(), (*lists.enemy)->getX(), (*lists.enemy)->getY());
			}
			if ((*lists.enemy)->Name != "box") {
				(*lists.enemy)->sprite->setRotation(actionGetRotation(hero.player->pos.xy.x, hero.player->pos.xy.y, (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y) + 90);
			}

			if (calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y) <= 500 && !(*lists.enemy)->angry) {
				game.sound->z_attack.play();
				(*lists.enemy)->angry = true;
			}
			
			eventZombieHustle(lists, hero);
			eventHitZombie(lists, hero, game.sound->z_pain);


			actionSlowMotion(game, game.time);
			eventZombieAtack(lists, hero, config, shoot, *game.sound);
		}

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
			if (hero.player->properties.life) {
				game.sound->win.play();
			}
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

			showMenu(*game.window, menu_text, *menu_info.text, *menu_img, menu_bool);
			showMission(*game.window, mission_text, *menu_info.text, hero, *menu_img);
		}
		else {
			gameProcces(config, game, hero, *lists, info, shoot, enemy, menu_bool, *menu_img);
		}


		if (menu_bool.restart) {
			//clearLists(*lists);
			lists.reset();
			lists = std::make_shared<Lists>();
			pushLists(config, *lists, game, enemy);
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