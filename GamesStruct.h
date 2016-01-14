#pragma once
#include "stdafx.h"
#include "Classes.h"
#include <list>
#include <vector>


struct Config {
	std::string icon = "./files/img/icon.png";
	std::string imageHeroPistol = "./files/sprites/player_pistol.png";
	std::string imageHeroUzi = "./files/sprites/player_uzi.png";
	std::string imageHeroShotgun = "./files/sprites/player_shotgun.png";
	std::string imageHeroMachinegun = "./files/sprites/player_machinegun.png";
	
	std::string imageHeroWarrior = "./files/img/heroWar.png";
	std::string aim = "./files/sprites/aim.png";
	std::vector<std::string> bloods{
		"./files/img/blood1.png",
		"./files/img/blood2.png",
		"./files/img/blood3.png"
	};

	std::vector<std::string> zombies =
	{
		"./files/sprites/citizenzombie1.png",
		"./files/sprites/citizenzombie2.png",
		"./files/sprites/citizenzombie3.png",
		"./files/sprites/citizenzombie4.png",
		"./files/sprites/citizenzombie5.png",
		"./files/sprites/citizenzombie6.png",
		"./files/sprites/citizenzombie7.png",
		"./files/sprites/citizenzombie8.png",
		"./files/sprites/citizenzombie9.png",
		"./files/sprites/citizenzombie10.png"
	};
	std::string boss = "./files/sprites/boss.png";
	std::string spitter = "./files/sprites/spitter.png";
	std::string box = "./files/sprites/box.png";

	std::string b_box = "./files/img/b_box.png";
	std::string Tree = "./files/img/tree1.png";
	std::string Spite = "./files/img/fly_slime.png";

	std::string Bullet = "./files/img/bullet1.png";
	std::string Blood = "./files/img/blood.png";

	std::string Shot = "./files/img/drob.png";
	std::string fon_music = "./files/music/fon.ogg";
	std::string map = "mappp.tmx";
	std::string font = "./files/fonts/birch111.ttf";
	std::string bonus = "./files/img/bonus/bonuses.png";

	std::string win = "./files/img/win.png";
	std::string lose = "./files/img/lose.png";

	std::string fon = "./files/sounds/fon.ogg";
	std::string menu = "./files/sounds/menu.ogg";
	std::string step_sound = "./files/sounds/step.ogg";
	std::string wave_sound = "./files/sounds/wave.wav";
	std::string z_call = "./files/sounds/z_call.wav";
	std::string shot_sound = "./files/sounds/shot.wav";
	std::string uzi = "./files/sounds/uzi.wav";
	std::string mgun = "./files/sounds/mgun.wav";
	std::string shotgun_sound = "./files/sounds/shootgun.wav";
	std::string cock = "./files/sounds/cock.wav";
	std::string pickup = "./files/sounds/pickup.wav";
	std::string zombie_hit = "./files/sounds/hit.wav";
	std::string move = "./files/sounds/move.wav";
	std::string pain = "./files/sounds/pain.wav";
	std::string z_pain = "./files/sounds/z_pain.wav";
	std::string dead = "./files/sounds/screem.wav";
	std::string win_sound = "./files/sounds/yes.wav";
	std::string z_dead = "./files/sounds/z_dead.wav";
	std::string z_attack = "./files/sounds/z_attack.wav";
};

struct sounds
{
	sf::Music music;
	sf::Music menu_music;

	sf::SoundBuffer shoot_buffer;
	sf::Sound shoot;

	sf::SoundBuffer uzi_buffer;
	sf::Sound uzi;

	sf::SoundBuffer mgun_buffer;
	sf::Sound mgun;

	sf::SoundBuffer shootgun_buffer;
	sf::Sound shootgun;

	sf::SoundBuffer pain_buffer;
	sf::Sound pain;

	sf::SoundBuffer dead_buffer;
	sf::Sound dead;

	sf::SoundBuffer win_buffer;
	sf::Sound win;

	sf::SoundBuffer z_dead_buffer;
	sf::Sound z_dead;

	sf::SoundBuffer z_attack_buffer;
	sf::Sound z_attack;

	sf::SoundBuffer z_pain_buffer;
	sf::Sound z_pain;

	sf::SoundBuffer zombie_hit_buffer;
	sf::Sound zombie_hit;

	sf::SoundBuffer move_buffer;
	sf::Sound move;

	sf::SoundBuffer step_buffer;
	sf::Sound step;

	sf::SoundBuffer wave_buffer;
	sf::Sound wave;

	sf::SoundBuffer z_call_buffer;
	sf::Sound z_call;

	sf::SoundBuffer cock_buffer;
	sf::Sound cock;

	sf::SoundBuffer pickup_buffer;
	sf::Sound pickup;

	sf::SoundBuffer deadBuffer;

};

struct Game1
{	
	std::shared_ptr<RenderWindow> window;
	std::shared_ptr<View> view1;
	std::shared_ptr<Level> lvl;
	std::shared_ptr<CollisionChecker> wallsChecker;
	std::shared_ptr<sounds> sound;


	std::shared_ptr<sf::Texture> finish_texture;
	std::shared_ptr<sf::Sprite> finish_sprite;

	std::shared_ptr<sf::Texture> aim_texture;
	std::shared_ptr<sf::Sprite> aim_sprite;

	Clock clock;
	Clock reload_clock;

	float time;
	float reload_time;

	Vector2i pixelPos;
	Vector2f pos;

	sf::Event event;

	const float EFFECT_TIME = 5000;
	float timer = 0;
	float speed_game = 1;



	bool is_end = false;
};


struct Hero
{
	std::shared_ptr<Player> player;
	Object player_obj = Object();
	std::string name = "Player1";
	float H = 71.0;
	float W = 50.0;
	int health = 150;
};

struct Shoot {
	std::shared_ptr<Bullet> bullet;
	float H = 20;
	float W = 20;
};

struct Blood {
	std::shared_ptr<sf::Texture> t_blood;
	std::shared_ptr<sf::Sprite> s_blood;
	Blood(std::string & file, Vector2f pos) {
		t_blood = std::make_shared<sf::Texture>();
		t_blood->loadFromFile(file);
		s_blood = std::make_shared<sf::Sprite>();
		s_blood->setTexture(*t_blood);
		s_blood->setOrigin(t_blood->getSize().x / 2, t_blood->getSize().y / 2);
		s_blood->setPosition(pos);
	}
};

struct Monster
{

	std::shared_ptr<Enemy> normal;
	float normal_H = 71.0;
	float normal_W = 71.0;
	int normal_health = 150;

	std::shared_ptr<Enemy> boss;
	float boss_H = 256.0;
	float boss_W = 256.0;
	int boss_health = 950;

	std::shared_ptr<Enemy> spitter;
	float spitter_H = 71.0;
	float spitter_W = 71.0;
	int spitter_health = 350;

	std::shared_ptr<Enemy> box;
	float box_H = 64.0;
	float box_W = 64.0;
	int box_health = 30;
};

struct Info
{
	Font font;
	std::shared_ptr<Text> text;
	int font_size = 20;
};


struct Lists
{
	std::list<std::shared_ptr<Enemy>>  entities;
	std::list<std::shared_ptr<Enemy>>::iterator enemy;
	std::list<std::shared_ptr<Enemy>>::iterator otherEnemy;

	std::list<std::shared_ptr<Slime>> spites;
	std::list<std::shared_ptr<Slime>>::iterator spit;

	std::list<std::shared_ptr<Blood>> bloods;
	std::list<std::shared_ptr<Blood>>::iterator puddle;

	std::list<std::shared_ptr<Bullet>> bullets;
	std::list<std::shared_ptr<Bullet>>::iterator bull;

	std::list<std::shared_ptr<Bonus>> bonuses;
	std::list<std::shared_ptr<Bonus>>::iterator bon;

	std::list<std::shared_ptr<Tree>> woods;
	std::list<std::shared_ptr<Tree>>::iterator wood;
};