#pragma once
#pragma once

float actionGetRotation(float to_x, float to_y, float from_x, float from_y);

void actionShotgunShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, Vector2f & pos);

void actionSingleShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, Vector2f & pos);

void actionUseAmmo(Hero & hero);

void actionShoot(Lists & lists, Hero & hero, Shoot & shoot, Config & config, Game1 & game, float reload_time, Vector2f & pos);

void actionSlowMotion(Game1 & game, float time);