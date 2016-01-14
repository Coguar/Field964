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
		shoot.bullet = std::make_shared<Bullet>(config.Shot, "Bullet", hero.player->pos.xy.x, hero.player->pos.xy.y, 10, 10, hero.player->dir);
		gototarget(shoot.bullet->pos.dxy.x, shoot.bullet->pos.dxy.y, pos.x - 20 + random_number(40), pos.y - 20 + random_number(40), hero.player->pos.xy.x, hero.player->pos.xy.y);
		lists.bullets.push_back(shoot.bullet);
	}
}

void actionSingleShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, Vector2f & pos) {
	float rotation = actionGetRotation(pos.x, pos.y, hero.player->pos.xy.x, hero.player->pos.xy.y);

	shoot.bullet = std::make_shared<Bullet>(config.Bullet, "Bullet",hero.player->pos.xy.x, hero.player->pos.xy.y, 20, 20, hero.player->dir);
	gototarget(shoot.bullet->pos.dxy.x, shoot.bullet->pos.dxy.y, pos.x, pos.y, hero.player->pos.xy.x, hero.player->pos.xy.y);
	shoot.bullet->sprite->setRotation(rotation);
	lists.bullets.push_back(shoot.bullet);
}

void actionUseAmmo(Hero & hero) {
	switch (hero.player->weapoons)
	{
	case Player::uzi : hero.player->ammo_uzi -= 1; break;
	case Player::shotgun: hero.player->ammo_shootgun -= 1; break;
	case Player::machinegun: hero.player->ammo_machinegun -= 1; break;
	}
}

void _gun_sound(Game1 & game, Hero & hero) {
	switch (hero.player->weapoons)
	{
	case Player::pistol: game.sound->shoot.play(); break;
	case Player::uzi: game.sound->uzi.play(); break;
	case Player::shotgun: game.sound->shootgun.play(); break;
	case Player::machinegun: game.sound->mgun.play(); break;
	}
}

float _gun_reload_time(Hero & hero) 
{
	if (hero.player->spray) {
		return hero.player->reload_auto_time;
	}
	else 
	{
		return hero.player->reload_nonauto_time;
	}
}

void _make_shot(Hero & hero, Lists & lists, Game1 & game, Shoot & shoot, Config & config, Vector2f & pos) {
	if (hero.player->ammo > 0 || hero.player->ammo == -1)
	{
		if (hero.player->weapoons != hero.player->shotgun)
		{
			actionSingleShoot(lists, hero, shoot, config, game, pos);

		}
		else if (hero.player->weapoons == hero.player->shotgun)
		{
			actionShotgunShoot(lists, hero, shoot, config, game, pos);
		}
		_gun_sound(game, hero);
		actionUseAmmo(hero);
	}
	else {
		game.sound->cock.play();

	}
}

void actionShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, float reload_time, Vector2f & pos) 
{
	
	float r_time = _gun_reload_time(hero);

	if (reload_time >= r_time) 
	{
		hero.player->reload = true;
	}
	if (hero.player->reload == true) 
	{
		game.reload_clock.restart();
		hero.player->reload = false;
		_make_shot(hero, lists, game, shoot, config, pos);

	}
}

void actionSlowMotion(Game1 & game, float time) {
	if (game.speed_game != 1) {
		game.timer += time;
		if (game.timer >= game.EFFECT_TIME) {
			game.timer = 0;
			game.speed_game = 1;
		}
	}
}