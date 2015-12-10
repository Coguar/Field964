#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "distantion.h"

void eventDropBonus(Lists * lists, Hero & hero, float time, Config & config) {
	for (lists->it = lists->entities.begin(); lists->it != lists->entities.end();) {
		(*lists->it)->update(time);
		if ((*lists->it)->life == false) {
			if (random_number(5) == 1) {
				lists->bonuses.push_back(new Bonus(config.bonus, random_number(3) + 1, (*lists->it)->x, (*lists->it)->y));
			}
			lists->it = lists->entities.erase(lists->it);
		}
		else {
			lists->it++;
		}
	}
}

void eventBulletDestroy(Lists * lists, Hero & hero, float time) {
	for (lists->bull = lists->bullets.begin(); lists->bull != lists->bullets.end(); ) {
		if ((*lists->bull)->life == false) {
			lists->bull = lists->bullets.erase(lists->bull);
		}
		else {
			lists->bull++;
		}
	}
}

void eventGetBonus(Lists * lists, Hero & hero, float time, float & speed) {
	for (lists->bon = lists->bonuses.begin(); lists->bon != lists->bonuses.end();) {
		if ((*lists->bon)->getRect().intersects(hero.player->getRect())) {
			if ((*lists->bon)->Name == 1) {
				hero.player->bonus_damage += 1.0;
			}
			else if ((*lists->bon)->Name == 2) {
				hero.player->health += 10;
			}
			else if ((*lists->bon)->Name == 3) {
				speed = 0.1;
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
}

void eventHitZombie(Lists * lists, Hero & hero, float time) {
	for (lists->bull = lists->bullets.begin(); lists->bull != lists->bullets.end();) {
		if ((*lists->it)->getRect().intersects((*lists->bull)->getRect())) {
			(*lists->it)->health = (*lists->it)->health - hero.player->damage;
			lists->bull = lists->bullets.erase(lists->bull);
		}

		else {
			lists->bull++;
		}
	}
}

void eventZombieAtack(Lists * lists, Hero & hero, float time) {
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

void eventZombieHustle(Lists * lists, Hero & hero) {
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
}
