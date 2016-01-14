#include "stdafx.h"
#include "GamesStruct.h"
#include "randomValue.h"
#include "Initiation.h"

void SoundInit(Config & config, Game1 & game) {
	game.sound->music.openFromFile(config.fon);
	game.sound->music.setLoop(true);
	game.sound->music.setVolume(10);

	game.sound->menu_music.openFromFile(config.menu);
	game.sound->menu_music.setLoop(true);
	//game.sound->menu_music.setVolume(10);

	game.sound->step_buffer.loadFromFile(config.step_sound);
	game.sound->step.setBuffer(game.sound->step_buffer);
	game.sound->step.setLoop(true);

	game.sound->wave_buffer.loadFromFile(config.wave_sound);
	game.sound->wave.setBuffer(game.sound->wave_buffer);

	game.sound->shoot_buffer.loadFromFile(config.shot_sound);
	game.sound->shoot.setBuffer(game.sound->shoot_buffer);
	game.sound->shoot.setVolume(5);

	game.sound->uzi_buffer.loadFromFile(config.uzi);
	game.sound->uzi.setBuffer(game.sound->uzi_buffer);
	game.sound->uzi.setVolume(5);

	game.sound->mgun_buffer.loadFromFile(config.mgun);
	game.sound->mgun.setBuffer(game.sound->mgun_buffer);
	game.sound->mgun.setVolume(5);

	game.sound->shootgun_buffer.loadFromFile(config.shotgun_sound);
	game.sound->shootgun.setBuffer(game.sound->shootgun_buffer);
	game.sound->shootgun.setVolume(5);

	game.sound->cock_buffer.loadFromFile(config.cock);
	game.sound->cock.setBuffer(game.sound->cock_buffer);
	game.sound->cock.setVolume(5);

	game.sound->pickup_buffer.loadFromFile(config.pickup);
	game.sound->pickup.setBuffer(game.sound->pickup_buffer);
	game.sound->pickup.setVolume(10);

	game.sound->move_buffer.loadFromFile(config.move);
	game.sound->move.setBuffer(game.sound->move_buffer);
	game.sound->move.setVolume(10);

	game.sound->pain_buffer.loadFromFile(config.pain);
	game.sound->pain.setBuffer(game.sound->pain_buffer);
	game.sound->pain.setVolume(10);

	game.sound->dead_buffer.loadFromFile(config.dead);
	game.sound->dead.setBuffer(game.sound->dead_buffer);
	game.sound->dead.setVolume(10);

	game.sound->win_buffer.loadFromFile(config.win_sound);
	game.sound->win.setBuffer(game.sound->win_buffer);
	game.sound->win.setVolume(10);

	game.sound->z_dead_buffer.loadFromFile(config.z_dead);
	game.sound->z_dead.setBuffer(game.sound->z_dead_buffer);
	game.sound->z_dead.setVolume(10);

	game.sound->z_attack_buffer.loadFromFile(config.z_attack);
	game.sound->z_attack.setBuffer(game.sound->z_attack_buffer);
	game.sound->z_attack.setVolume(10);

	game.sound->z_pain_buffer.loadFromFile(config.z_pain);
	game.sound->z_pain.setBuffer(game.sound->z_pain_buffer);
	game.sound->z_pain.setVolume(10);

	game.sound->z_call_buffer.loadFromFile(config.z_call);
	game.sound->z_call.setBuffer(game.sound->z_call_buffer);
	game.sound->z_call.setVolume(10);

	game.sound->zombie_hit_buffer.loadFromFile(config.zombie_hit);
	game.sound->zombie_hit.setBuffer(game.sound->zombie_hit_buffer);
	game.sound->zombie_hit.setVolume(10);

}

void GameInit(Config & config, Game1 & game, Hero & hero)
{
	game.is_end = false;

	game.window = std::make_shared<RenderWindow>(sf::VideoMode(800, 600), "Game");
	game.lvl = std::make_shared<Level>();
	game.lvl->LoadFromFile(config.map);

	game.sound = std::make_shared<sounds>();
	SoundInit(config, game);
	hero.player_obj = game.lvl->GetObject("player1");
	game.wallsChecker = std::make_shared<CollisionChecker>(game.lvl);
	hero.player = std::make_shared<Player>(config.imageHeroPistol, hero.name, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);

	game.view1 = std::make_shared<View>();
	game.view1->setSize(800, 600);

}

void GameReInit(Config & config, Game1 & game, Hero & hero)
{
	game.is_end = false;

	hero.player_obj = game.lvl->GetObject("player1");
	hero.player = std::make_shared<Player>(config.imageHeroPistol, hero.name, hero.player_obj.rect.left, hero.player_obj.rect.top, hero.W, hero.H, hero.health);
}

void FinishGameInit(Config & config, Game1 & game, bool & life) {
	game.finish_texture = std::make_shared<Texture>();
	game.finish_sprite = std::make_shared<Sprite>();
	if (life) {
		game.finish_texture->loadFromFile(config.win);
	}
	else {
		game.finish_texture->loadFromFile(config.lose);
	}
	game.finish_sprite->setTexture(*game.finish_texture);
	game.finish_sprite->setOrigin(game.finish_texture->getSize().x / 2, game.finish_texture->getSize().y / 2);
}

void InfoInit(Config & config, Info & info)
{
	info.font.loadFromFile(config.font);
	info.text = std::make_shared<Text>("", info.font, info.font_size);
	info.text->setColor(Color::Red);
	info.text->setStyle(Text::Bold);
}
