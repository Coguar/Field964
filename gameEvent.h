#pragma once

void eventDropBonus(Lists & lists, Hero & hero, float time, Config & config, CollisionChecker & checker);

void eventBulletDestroy(Lists & lists, Hero & hero, float time);

void eventGetBonus(Lists & lists, Hero & hero, float time, float & speed);

void eventHitZombie(Lists & lists, Hero & hero, float time);

void eventZombieAtack(Lists & lists, Hero & hero, float time);

void eventZombieHustle(Lists & lists, Hero & hero);