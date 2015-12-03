#include "stdafx.h"
/*#include "randomValue.h"

void eventDropBonus(Lists & lists, Hero & hero, float time, Config & config) {
	for (lists.it = lists.entities.begin(); lists.it != lists.entities.end();) {
		(*lists.it)->update(time);
		if ((*lists.it)->life == false) {
			if (random_number(5) == 1) {
				lists.bonuses.push_back(new Bonus(config.bonus, random_number(3) + 1, (*lists.it)->x, (*lists.it)->y));
			}
			lists.it = lists.entities.erase(lists.it);
		}
		else {
			lists.it++;
		}
	}
}

void eventBulletDestroy(Lists & lists, Hero & hero, float time) {
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end(); ) {
		(*lists.bull)->update(time);
		if ((*lists.bull)->life == false) {
			lists.bull = lists.bullets.erase(lists.bull);
		}
		else {
			lists.bull++;
		}
	}
}

void eventGetBonus(Lists & lists, Hero & hero, float time) {
	for (lists.bon = lists.bonuses.begin(); lists.bon != lists.bonuses.end();) {
		if ((*lists.bon)->getRect().intersects(hero.player->getRect())) {
			lists.bon = lists.bonuses.erase(lists.bon);
			if ((*lists.bon)->Name == 1) {
				hero.player->health += 10;
			}
			else if ((*lists.bon)->Name == 2) {
				hero.player->health += 10;
			}
			else {
				hero.player->health += 10;
			}
		}
		else {
			lists.bon++;
		}
	}
}

void eventHitZombie(Lists & lists, Hero & hero, float time) {
	for (lists.bull = lists.bullets.begin(); lists.bull != lists.bullets.end();) {
		if ((*lists.it)->getRect().intersects((*lists.bull)->getRect())) {
			(*lists.it)->health = (*lists.it)->health - 20;
			lists.bull = lists.bullets.erase(lists.bull);
		}

		else {
			lists.bull++;
		}
	}
}

void eventZombieAtack(Lists & lists, Hero & hero, float time) {
	if ((*lists.it)->getRect().intersects(hero.player->getRect())) {
		(*lists.it)->player_contact = true;
		if (int(time) % 10 == 0) {
			hero.player->health = hero.player->health - 0;
		}

	}
	else {
		(*lists.it)->player_contact = false;
	}
}*/