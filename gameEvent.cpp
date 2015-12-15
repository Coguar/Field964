#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "gameEvent.h"
#include "GameMath.h"
#include <algorithm>

namespace
{
	bool _is_crash(Bullet * bull) {
		return bull->life == false;
	}
}
void eventDropBonus(Lists & lists, Hero & hero, float time, Config & config) {
	for (lists.it = lists.entities.begin(); lists.it != lists.entities.end();) {
		(*lists.it)->update(time);
		if ((*lists.it)->properties.life == false) {
			if (random_number(5) == 1) {
				lists.bonuses.push_back(new Bonus(config.bonus, random_number(6) + 1, (*lists.it)->pos.xy.x, (*lists.it)->pos.xy.y));
			}
			lists.it = lists.entities.erase(lists.it);
		}
		else {
			lists.it++;
		}
	}
}

void eventBulletDestroy(Lists & lists, Hero & hero, float time) {
	lists.bullets.erase( remove_if(lists.bullets.begin(), lists.bullets.end(), _is_crash), lists.bullets.end());
}

void eventGetBonus(Lists & lists, Hero & hero, float time, float & speed) {
	for (lists.bon = lists.bonuses.begin(); lists.bon != lists.bonuses.end();) {
		if ((*lists.bon)->getRect().intersects(hero.player->getRect())) {
			std::cout << (*lists.bon)->Name;
			if ((*lists.bon)->Name == 1) {
				hero.player->bonus_damage += 1.0;
			}
			else if ((*lists.bon)->Name == 2) {
				hero.player->properties.health += 10;
			}
			else if ((*lists.bon)->Name == 3) {
				speed = 0.1f;
			}
			else if ((*lists.bon)->Name == 4) {
				hero.player->ammo_uzi += 15;
			}
			else if ((*lists.bon)->Name == 5) {
				hero.player->ammo_machinegun += 30;
			}
			else if ((*lists.bon)->Name == 6) {
				hero.player->ammo_shootgun += 4;
			}
			else if ((*lists.bon)->Name == 7) {
				hero.player->take_uzi = true;
			}
			else if ((*lists.bon)->Name == 8) {
				hero.player->take_shotgun = true;
			}
			else if ((*lists.bon)->Name == 9) {
				hero.player->take_machinegun = true;
			}
			else {
				hero.player->take_bucket = true;
			}
			lists.bon = lists.bonuses.erase(lists.bon);
		}
		else {
			lists.bon++;
		}
	}
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
	for (lists.it2 = lists.entities.begin(); lists.it2 != lists.entities.end(); lists.it2++) {
		if ((*lists.it2)->getRect() != (*lists.it)->getRect()) {
			if ((*lists.it2)->getRect().intersects((*lists.it)->getRect())) {
				if (calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists.it)->getX(), (*lists.it)->getY()) > calculateDistantion(hero.player->getX(), hero.player->getY(), (*lists.it2)->getX(), (*lists.it2)->getY())) {
					(*lists.it)->pos.xy.x = (*lists.it)->pos.xy.x - (*lists.it)->Xdir;
					(*lists.it)->pos.xy.y = (*lists.it)->pos.xy.y - (*lists.it)->Ydir;
				}
				else {
					(*lists.it2)->pos.xy.x = (*lists.it2)->pos.xy.x - (*lists.it2)->Xdir;
					(*lists.it2)->pos.xy.y = (*lists.it2)->pos.xy.y - (*lists.it2)->Ydir;
				}
			}

		}
	}
}
