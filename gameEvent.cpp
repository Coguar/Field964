#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "GameMath.h"
#include <algorithm>
#include <functional>
#include <memory>
#include "GoToTarget.h"
#include "action.h"
#include "Initiation.h"

namespace
{
	bool _is_crash(Bullet * bull) {
		return bull->life == false;
	}
}
void eventDropBonus(Lists & lists, Hero & hero, Game1 & game, Config & config) {
	for (auto it : lists.entities) {
		it->update(game.time * game.speed_game, *game.wallsChecker, hero.player->pos.xy.x, hero.player->pos.xy.y);
		if (it->properties.life == false) {
			if (random_number(5) == 1) {
				lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, random_number(6) + 1, it->pos.xy.x, it->pos.xy.y));
			}
			if (it->Name != "box") {
				game.sound->z_dead.play();
				lists.bloods.push_back(std::make_shared<Blood>(config.bloods[random_number(3)], it->pos.xy));
			}
			else {
				lists.bloods.push_back(std::make_shared<Blood>(config.b_box, it->pos.xy));

			}
		}
	}
	auto is_die = [](std::shared_ptr<Enemy> enemy) { return !(enemy->properties.life); };
	lists.entities.erase(remove_if(lists.entities.begin(), lists.entities.end(), is_die), lists.entities.end());

}

bool _createSlimePuddle(std::shared_ptr<Bullet> bull, Lists & lists, Game1 & game, Config & config) {
	if (bull->life == false) {
		if (bull->name == "Spite") {
			lists.spites.push_back(std::make_shared<Slime>(bull->pos.xy.x, bull->pos.xy.y));
		}
		else {
			bull->texture->loadFromFile(config.Blood);
			bull->sprite->setTexture(*bull->texture);
			game.window->draw(*bull->sprite);
		}
	}
	return !(bull->life);
}

void eventBulletDestroy(Config & config, Lists & lists, Hero & hero, Game1 & game) {
	std::function<bool(std::shared_ptr<Bullet>)> is_crash(std::bind(_createSlimePuddle, std::placeholders::_1, std::ref(lists), std::ref(game), config));
	lists.bullets.erase( remove_if(lists.bullets.begin(), lists.bullets.end(), is_crash), lists.bullets.end());
}

bool _bonus_type(std::shared_ptr<Bonus> bon, Hero & hero, Game1 & game) {
	if (bon->getRect().intersects(hero.player->getRect())) {
		game.sound->pickup.play();
		switch (bon->Name)
		{
		case 1: hero.player->bonus_damage += 1.0; break;
		case 2: hero.player->properties.health += 10; break;
		case 3: game.speed_game = 0.1f; break;
		case 4: hero.player->ammo_uzi += 15; break;
		case 5: hero.player->ammo_machinegun += 30; break;
		case 6: hero.player->ammo_shootgun += 4; break;
		case 7: hero.player->m_Guns.push_back(hero.player->uzi); std::sort(hero.player->m_Guns.begin(), hero.player->m_Guns.end()); break;
		case 8: hero.player->m_Guns.push_back(hero.player->shotgun); std::sort(hero.player->m_Guns.begin(), hero.player->m_Guns.end()); break;
		case 9: hero.player->m_Guns.push_back(hero.player->machinegun); std::sort(hero.player->m_Guns.begin(), hero.player->m_Guns.end()); break;
		case 10: hero.player->take_bucket = true; break;
		}
		return true;
	}
	return false;
}

void eventGetBonus(Lists & lists, Hero & hero, float time, Game1 & game) {
	std::function<bool(std::shared_ptr<Bonus>)> func(std::bind(_bonus_type, std::placeholders::_1, hero, std::ref(game)));
	lists.bonuses.erase(remove_if(lists.bonuses.begin(), lists.bonuses.end(), func), lists.bonuses.end());
}

void eventHitZombie(Lists & lists, Hero & hero, sf::Sound & sound) {
	(*lists.enemy)->sprite->setColor(Color::White);
	for (std::shared_ptr<Bullet> bull : lists.bullets) {
		if ((*lists.enemy)->getRect().intersects(bull->getRect()) && bull->name != "Spite") {
			(*lists.enemy)->properties.health = (*lists.enemy)->properties.health - int(hero.player->damage);
			if ((*lists.enemy)->Name != "box") {
				sound.play();
			}
			(*lists.enemy)->sprite->setColor(Color::Red);
			bull->life = false;
		}
	}
}

void _spitterAtack(Lists & lists, Hero & hero, Config & config, Shoot & shoot) {
	if ((*lists.enemy)->Name == "spitter") {
		if ((*lists.enemy)->shooting && calculateDistantion(hero.player->pos.xy.x, hero.player->pos.xy.y, (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y) <= 640) {
			float rotation = actionGetRotation(hero.player->pos.xy.x, hero.player->pos.xy.y, (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y);

			shoot.bullet = std::make_shared<Bullet>(config.Spite, "Spite", (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y, hero.player->pos.xy.x, hero.player->pos.xy.y, hero.player->dir);
			gototarget(shoot.bullet->pos.dxy.x, shoot.bullet->pos.dxy.y, hero.player->pos.xy.x, hero.player->pos.xy.y, (*lists.enemy)->pos.xy.x, (*lists.enemy)->pos.xy.y);
			shoot.bullet->sprite->setRotation(rotation + 90);
			(*lists.enemy)->shooting = false;
			lists.bullets.push_back(shoot.bullet);
		}
	}
}

void eventZombieAtack(Lists & lists, Hero & hero, Config & config, Shoot & shoot, sounds & sound) {
	_spitterAtack(lists, hero, config, shoot);
	if ((*lists.enemy)->getRect().intersects(hero.player->getRect())) {
		(*lists.enemy)->player_contact = true;
		if ((*lists.enemy)->hit == true) {
			if ((*lists.enemy)->Name != "box") {
				sound.zombie_hit.play();
				sound.pain.play();
			}
			else {
				sound.move.play();
			}
			hero.player->properties.health = hero.player->properties.health - (*lists.enemy)->damage;
			(*lists.enemy)->hit = false;
		}
	}
	else {
		(*lists.enemy)->player_contact = false;
	}
}

void eventZombieHustle(Lists & lists, Hero & hero) {
	for (std::shared_ptr<Enemy> otherEnemy : lists.entities) {
		if (otherEnemy->getRect() != (*lists.enemy)->getRect()) {
			if (otherEnemy->getRect().intersects((*lists.enemy)->getRect())) {
				if (calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists.enemy)->getX(), (*lists.enemy)->getY()) > calculateDistantion(hero.player->getX(), hero.player->getY(), otherEnemy->getX(), otherEnemy->getY())) {
					(*lists.enemy)->pos.xy.x = (*lists.enemy)->pos.xy.x - (*lists.enemy)->dir.x;
					(*lists.enemy)->pos.xy.y = (*lists.enemy)->pos.xy.y - (*lists.enemy)->dir.y;
				}
				else {
					otherEnemy->pos.xy.x = otherEnemy->pos.xy.x - otherEnemy->dir.x;
					otherEnemy->pos.xy.y = otherEnemy->pos.xy.y - otherEnemy->dir.y;
				}
			}

		}
	}
}

void eventPuddleDestroy(Lists & lists) {
	auto _end_burn = [](std::shared_ptr<Slime> puddle) {return !(puddle->life); };
	lists.spites.erase(remove_if(lists.spites.begin(), lists.spites.end(), _end_burn), lists.spites.end());
}

void eventBurningAcid(Lists & lists, Hero & hero, float time) {
	for (std::shared_ptr<Slime> puddle : lists.spites) {
		puddle->update(time);
		if (puddle->getRect().intersects(hero.player->getRect()) && puddle->hit) {
			hero.player->properties.health = hero.player->properties.health - puddle->damage;
			puddle->hit = false;
		}
	}
}

void eventZombieStopHero(Lists & lists, Hero & hero) {
	hero.player->contact = false;
	for (auto & enemy : lists.entities) {
		if (hero.player->getRect1().intersects(enemy->getRect())) {
			hero.player->contact = true;
			enemy->pos.xy.x -= enemy->dir.x;
			enemy->pos.xy.y -= enemy->dir.y;
		}
	}
}

void _addZombies(std::string Name, std::string file, Game1 & game, Monster & enemy, Lists & lists) {
	std::vector<Object> e;
	String name;

	e = game.lvl->GetObjects(Name);
	name = file;
	for (size_t i = 0; i < e.size(); i++) {
		enemy.spitter = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter");
		enemy.spitter->angry = true;
		lists.entities.push_back(enemy.spitter);
		enemy.spitter.reset();

	}
}

void eventNewWave(Config & config, Lists & lists, Game1 & game, Monster & enemy) {
	std::vector<Object> e = game.lvl->GetObjects("normal1");
	String name;
	int number;

	for (size_t i = 0; i < e.size() - 1; i++) {
		number = (random_number(10));
		name = config.zombies[number];
		enemy.normal = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal");
		enemy.normal->angry = true;
		lists.entities.push_back(enemy.normal);
		enemy.normal.reset();
	}

	e = game.lvl->GetObjects("spitter1");
	name = config.spitter;
	for (size_t i = 0; i < e.size(); i++) {
		enemy.spitter = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter");
		enemy.spitter->angry = true;
		lists.entities.push_back(enemy.spitter);
		enemy.spitter.reset();

	}

	e = game.lvl->GetObjects("boss1");
	name = config.boss;
	for (size_t i = 0; i < e.size(); i++) {
		enemy.boss = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");
		enemy.boss->angry = true;
		lists.entities.push_back(enemy.boss);
		enemy.boss.reset();
	}
}

void eventZombiesWave(Hero & hero, Game1 & game, Config & config, Lists & lists, Monster & enemy) {
	if (hero.player->quest_move) {
		game.sound->z_call.play();
		game.sound->wave.play();
		eventNewWave(config, lists, game, enemy);
		hero.player->quest_move = false;
	}
}

void eventGetTrees(Config & config, Lists & lists, Game1 & game)
{
	std::vector<Object> e = game.lvl->GetObjects("tree");
	for (size_t i = 0; i < e.size(); i++) {
		lists.woods.push_back(std::make_shared<Tree>(config.Tree, e[i].rect.left, e[i].rect.top));
	}
}

void eventGetGuns(Config & config, Lists & lists, Game1 & game)
{
	std::vector<Object> e = game.lvl->GetObjects("uzi");
	for (size_t i = 0; i < e.size(); i++) {
		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 7, e[i].rect.left, e[i].rect.top));
	}
	e = game.lvl->GetObjects("shotgun");
	for (size_t i = 0; i < e.size(); i++) {
		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 8, e[i].rect.left, e[i].rect.top));
	}
	e = game.lvl->GetObjects("machinegun");
	for (size_t i = 0; i < e.size(); i++) {
		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 9, e[i].rect.left, e[i].rect.top));
	}
	e = game.lvl->GetObjects("bucket");
	for (size_t i = 0; i < e.size(); i++) {
		lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, 10, e[i].rect.left, e[i].rect.top));
	}
}


void eventGetEnemys(Config & config, Lists & lists, Game1 & game, Monster & enemy)
{
	std::vector<Object> e = game.lvl->GetObjects("box");
	String name;
	int number;

	name = config.box;
	for (size_t i = 0; i < e.size(); i++) {
		//enemy.boss = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");

		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.box_W, enemy.box_H, "box"));
	}

	e = game.lvl->GetObjects("normal");
	for (size_t i = 0; i < e.size() - 1; i++) {
		number = (random_number(10));
		name = config.zombies[number];
		//	enemy.normal = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal");
		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.normal_W, enemy.normal_H, "normal"));
		//enemy.normal.reset();
	}

	e = game.lvl->GetObjects("spitter");
	name = config.spitter;
	for (size_t i = 0; i < e.size(); i++) {
		//enemy.spitter = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter");

		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.spitter_W, enemy.spitter_H, "spitter"));
		enemy.spitter.reset();

	}

	e = game.lvl->GetObjects("boss");
	name = config.boss;
	for (size_t i = 0; i < e.size(); i++) {
		//enemy.boss = std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss");

		lists.entities.push_back(std::make_shared<Enemy>(name, e[i].rect.left, e[i].rect.top, enemy.boss_W, enemy.boss_H, "boss"));
		enemy.boss.reset();
	}



}