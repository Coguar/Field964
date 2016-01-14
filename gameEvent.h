#pragma once

void eventDropBonus(Lists & lists, Hero & hero, Game1 & game, Config & config);

void eventBulletDestroy(Config & config, Lists & lists, Hero & hero, Game1 & game);

void eventGetBonus(Lists & lists, Hero & hero, float time, Game1 & game);

void eventHitZombie(Lists & lists, Hero & hero, sf::Sound & sound);

void eventZombieAtack(Lists & lists, Hero & hero, Config & config, Shoot & shoot, sounds & sound);

void eventZombieHustle(Lists & lists, Hero & hero);

void eventPuddleDestroy(Lists & lists);

void eventBurningAcid(Lists & lists, Hero & hero, float time);

void eventZombieStopHero(Lists & lists, Hero & hero);

void eventNewWave(Config & config, Lists & lists, Game1 & game, Monster & enemy);

void eventZombiesWave(Hero & hero, Game1 & game, Config & config, Lists & lists, Monster & enemy);

void eventGetTrees(Config & config, Lists & lists, Game1 & game);

void eventGetGuns(Config & config, Lists & lists, Game1 & game);

void eventGetEnemys(Config & config, Lists & lists, Game1 & game, Monster & enemy);