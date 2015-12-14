#include "stdafx.h"
#include "GamesStruct.h"
#include "GoToTarget.h"
#include "randomValue.h"
#include "action.h"
#define _USE_MATH_DEFINES
#include <math.h>

float actionGetRotation(float to_x, float to_y, float from_x, float from_y) {
	float X = to_x - from_x;
	float Y = to_y - from_y;
	float rotation = float((atan2(Y, X)) * 180 / M_PI);
	return rotation;
}

void actionShotgunShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, Vector2f & pos) {
	for (int i = 0; i < 7; i++) {
		shoot.bullet = new Bullet(config.Shot, "Bullet", *game.lvl, hero.player->pos.x, hero.player->pos.y, 10, 10, hero.player->dir);
		gototarget(shoot.bullet->pos.dx, shoot.bullet->pos.dy, pos.x - 20 + random_number(40), pos.y - 20 + random_number(40), hero.player->pos.x, hero.player->pos.y);
		lists.bullets.push_back(shoot.bullet);
	}
}

void actionSingleShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, Vector2f & pos) {
	float rotation = actionGetRotation(pos.x, pos.y, hero.player->pos.x, hero.player->pos.y);

	shoot.bullet = new Bullet(config.Bullet, "Bullet", *game.lvl, hero.player->pos.x, hero.player->pos.y, 20, 20, hero.player->dir);
	gototarget(shoot.bullet->pos.dx, shoot.bullet->pos.dy, pos.x, pos.y, hero.player->pos.x, hero.player->pos.y);
	shoot.bullet->sprite->setRotation(rotation);
	lists.bullets.push_back(shoot.bullet);
}

void actionUseAmmo(Hero & hero) {
	switch (hero.player->gun)
	{
	case 1: hero.player->ammo_uzi -= 1; break;
	case 2: hero.player->ammo_shootgun -= 1; break;
	case 3: hero.player->ammo_machinegun -= 1; break;
	}
}

void actionShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, float reload_time, Vector2f & pos) {
	
	if (reload_time >= hero.player->reload_time) {
		hero.player->reload = true;
	}
	if (hero.player->reload == true) {
		hero.player->reload = false;

		if (hero.player->ammo > 0 || hero.player->ammo == -1) {
			if (hero.player->weapoon != hero.player->shotgun) {
				actionSingleShoot(lists, hero, shoot, config, game, pos);
			}
			else if(hero.player->weapoon == hero.player->shotgun){
				actionShotgunShoot(lists, hero, shoot, config, game, pos);
			}
			actionUseAmmo(hero);
		}

	}
}

void actionSlowMotion(Game1 & game, float time) {
	if (game.speed_game != 1) {
		game.timer += time;
		if (game.timer >= 1000) {
			game.timer = 0;
			game.speed_game = 1;
		}
	}
}