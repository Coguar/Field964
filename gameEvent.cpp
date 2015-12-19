#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "GameMath.h"
#include <algorithm>
#include <functional>
#include <memory>

namespace
{
	bool _is_crash(Bullet * bull) {
		return bull->life == false;
	}
}
void eventDropBonus(Lists & lists, Hero & hero, float time, Config & config, CollisionChecker & checker) {
	for (auto it : lists.entities) {
		it->update(time, checker);
		if (it->properties.life == false) {
			if (random_number(5) == 1) {
				lists.bonuses.push_back(std::make_shared<Bonus>(config.bonus, random_number(6) + 1, it->pos.xy.x, it->pos.xy.y));
			}
		}
	}
	auto is_die = [](std::shared_ptr<Enemy> enemy) { return !(enemy->properties.life); };
	lists.entities.erase(remove_if(lists.entities.begin(), lists.entities.end(), is_die), lists.entities.end());

}

void eventBulletDestroy(Lists & lists, Hero & hero, float time) {
	auto is_crash = [](std::shared_ptr<Bullet>bull) { return !(bull->life); };
	lists.bullets.erase( remove_if(lists.bullets.begin(), lists.bullets.end(), is_crash), lists.bullets.end());
}

bool _bonus_type(std::shared_ptr<Bonus> bon, Hero & hero, float & speed) {
	if (bon->getRect().intersects(hero.player->getRect())) {
		switch (bon->Name)
		{
		case 1: hero.player->bonus_damage += 1.0; break;
		case 2: hero.player->properties.health += 10; break;
		case 3: speed = 0.1f; break;
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

void eventGetBonus(Lists & lists, Hero & hero, float time, float & speed) {
	std::function<bool(std::shared_ptr<Bonus>)> func(std::bind(_bonus_type, std::placeholders::_1, hero, speed));
	lists.bonuses.erase(remove_if(lists.bonuses.begin(), lists.bonuses.end(), func), lists.bonuses.end());
}

void eventHitZombie(Lists & lists, Hero & hero, float time) {
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); lists.bull++) {
		if ((*lists.enemy)->getRect().intersects((*lists.bull)->getRect())) {
			(*lists.enemy)->properties.health = (*lists.enemy)->properties.health - int(hero.player->damage);
			(*lists.bull)->life = false;
		}
	}
}

void eventZombieAtack(Lists & lists, Hero & hero, float time) {
	if ((*lists.enemy)->getRect().intersects(hero.player->getRect())) {
		(*lists.enemy)->player_contact = true;
		if (int(time) % 10 == 0) {
			hero.player->properties.health = hero.player->properties.health - 0;
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
					(*lists.enemy)->pos.xy.x = (*lists.enemy)->pos.xy.x - (*lists.enemy)->Xdir;
					(*lists.enemy)->pos.xy.y = (*lists.enemy)->pos.xy.y - (*lists.enemy)->Ydir;
				}
				else {
					otherEnemy->pos.xy.x = otherEnemy->pos.xy.x - otherEnemy->Xdir;
					otherEnemy->pos.xy.y = otherEnemy->pos.xy.y - otherEnemy->Ydir;
				}
			}

		}
	}
}
