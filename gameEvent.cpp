#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "GameMath.h"
#include <algorithm>
#include <functional>

namespace
{
	bool _is_crash(Bullet * bull) {
		return bull->life == false;
	}
}
void eventDropBonus(Lists & lists, Hero & hero, float time, Config & config) {
	for (auto it : lists.entities) {
		it->update(time);
		if (it->properties.life == false) {
			if (random_number(5) == 1) {
				lists.bonuses.push_back(new Bonus(config.bonus, random_number(6) + 1, it->pos.xy.x, it->pos.xy.y));
			}
		}
	}
	auto is_die = [](Enemy *enemy) { return !(enemy->properties.life); };
	lists.entities.erase(remove_if(lists.entities.begin(), lists.entities.end(), is_die), lists.entities.end());

}

void eventBulletDestroy(Lists & lists, Hero & hero, float time) {
	auto is_crash = [](Bullet *bull) { return !(bull->life); };
	lists.bullets.erase( remove_if(lists.bullets.begin(), lists.bullets.end(), is_crash), lists.bullets.end());
}

bool _bonus_type(Bonus * bon, Hero & hero, float & speed) {
	if (bon->getRect().intersects(hero.player->getRect())) {
		switch (bon->Name)
		{
		case 1: hero.player->bonus_damage += 1.0; break;
		case 2: hero.player->properties.health += 10; break;
		case 3: speed = 0.1f; break;
		case 4: hero.player->ammo_uzi += 15; break;
		case 5: hero.player->ammo_machinegun += 30; break;
		case 6: hero.player->ammo_shootgun += 4; break;
		case 7: hero.player->take_uzi = true; break;
		case 8: hero.player->take_shotgun = true; break;
		case 9: hero.player->take_machinegun = true; break;
		case 10: hero.player->take_bucket = true; break;
		}
		return true;
	}
	return false;
}

void eventGetBonus(Lists & lists, Hero & hero, float time, float & speed) {
	std::function<bool(Bonus*)> func(std::bind(_bonus_type, std::placeholders::_1, hero, speed));
	lists.bonuses.erase(remove_if(lists.bonuses.begin(), lists.bonuses.end(), func), lists.bonuses.end());
}

void eventHitZombie(Lists & lists, Hero & hero, float time) {
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); lists.bull++) {
		if ((*lists.it)->getRect().intersects((*lists.bull)->getRect())) {
			(*lists.it)->properties.health = (*lists.it)->properties.health - int(hero.player->damage);
			(*lists.bull)->life = false;
		}
	}
}

void eventZombieAtack(Lists & lists, Hero & hero, float time) {
	if ((*lists.it)->getRect().intersects(hero.player->getRect())) {
		(*lists.it)->player_contact = true;
		if (int(time) % 10 == 0) {
			hero.player->properties.health = hero.player->properties.health - 0;
		}

	}
	else {
		(*lists.it)->player_contact = false;
	}
}

void eventZombieHustle(Lists & lists, Hero & hero) {
	for (Enemy * it2 : lists.entities) {
		if (it2->getRect() != (*lists.it)->getRect()) {
			if (it2->getRect().intersects((*lists.it)->getRect())) {
				if (calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists.it)->getX(), (*lists.it)->getY()) > calculateDistantion(hero.player->getX(), hero.player->getY(), it2->getX(), it2->getY())) {
					(*lists.it)->pos.xy.x = (*lists.it)->pos.xy.x - (*lists.it)->Xdir;
					(*lists.it)->pos.xy.y = (*lists.it)->pos.xy.y - (*lists.it)->Ydir;
				}
				else {
					it2->pos.xy.x = it2->pos.xy.x - it2->Xdir;
					it2->pos.xy.y = it2->pos.xy.y - it2->Ydir;
				}
			}

		}
	}
}
