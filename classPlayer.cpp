#include "classPlayer.h"



/*Player::Player(String F, String Name, Level &lev, float X, float Y, float W, float H, int health_point) :Entity(image, Name, X, Y, W, H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	obj = lev.GetAllObjects();

	properties.health = health_point;
	File = F;//имя файла+расширение
	properties.w = W; properties.h = H;//высота и ширина
	image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
	texture->loadFromImage(image);//закидываем наше изображение в текстуру
	sprite->setTexture(*texture);//заливаем спрайт текстурой
	pos.xy.x = X; pos.xy.y = Y;//координата появления спрайта
	sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h)));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	weapoon = pistol;

	float x1, y1 = 0;
	float damage = 20.0;
	float reload_time = 0.1f;
	int dir = 0;
	int quest = 0;
	bool reload = true;
	int gun = 0;

	bool take_uzi = false;
	bool take_shotgun = false;
	bool take_machinegun = false;
	bool take_bucket = false;

	float damage_pistol = 10;
	float damage_uzi = 15;
	float damage_shotgun = 5;
	float damage_machinegun = 20;
	float bonus_damage = 0;

	int ammo_uzi = 25;
	int ammo_shootgun = 8;
	int ammo_machinegun = 100;
	int ammo = 0;

	int choose_gun = 1;
}*/

void Player::_chose_gun() {
	bool set_gun = false;
	while (set_gun == false) {
		switch (gun) {
		case 0: weapoon = pistol; set_gun = true;  break;
		case 1: weapoon = uzi;  if (take_uzi == false) { gun += choose_gun; }
				else { set_gun = true; }
				break;
		case 2: weapoon = shotgun; if (take_shotgun == false) { gun += choose_gun; }
				else { set_gun = true; }
				break;
		case 3: weapoon = machinegun; if (take_machinegun == false) { gun += choose_gun; if (choose_gun == 1) { gun = 0; } }
				else { set_gun = true; }
				break;
		}
	}
}

void Player::_take_gun() {
	switch (weapoon) {
	case pistol: image.loadFromFile("./files/sprites/player_pistol.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
		damage = damage_pistol + bonus_damage;  ammo = -1; break;
	case uzi: if (take_uzi == true) {
		image.loadFromFile("./files/sprites/player_uzi.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(8, 0, 50, int(properties.h))); sprite->setOrigin(float(properties.w / 2), float(properties.h / 2));
	}
			  damage = damage_uzi + bonus_damage; ammo = ammo_uzi;  break;
	case shotgun:if (take_shotgun == true) {
		image.loadFromFile("./files/sprites/player_shotgun.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
	}
				 damage = damage_shotgun + bonus_damage; ammo = ammo_shootgun;  break;
	case machinegun: if (take_machinegun == true) {
		image.loadFromFile("./files/sprites/player_machinegun.png"); texture->loadFromImage(image);
		sprite->setTextureRect(IntRect(3, 0, 68, 100)); sprite->setOrigin(float(properties.w / 2 + 11), float(100 / 2));
	}
					 damage = damage_machinegun + bonus_damage; ammo = ammo_machinegun;  break;
	}
}


void Player::_set_speed() {
	float speed = properties.speed;
	if (quest == 4 && take_bucket == true) {
		speed = properties.speed * 0.5f;
	}
	switch (dir) {
	case 0: pos.dx = speed; pos.dy = 0;   break;
	case 1: pos.dx = -speed; pos.dy = 0;   break;
	case 2: pos.dx = 0; pos.dy = speed;   break;
	case 3: pos.dx = 0; pos.dy = -speed;   break;
	case 4: pos.dx = float(speed * 0.66); pos.dy = float(speed * 0.66);   break;
	case 5: pos.dx = float(speed * 0.66); pos.dy = float(-speed * 0.66);   break;
	case 6: pos.dx = float(-speed * 0.66); pos.dy = float(-speed * 0.66);   break;
	case 7: pos.dx = float(-speed * 0.66); pos.dy = float(speed * 0.66);   break;
	}
}

void Player::update(float time, CollisionChecker & checker) {
	x1 = pos.xy.x;
	y1 = pos.xy.y;

	_chose_gun();
	_take_gun();
	_set_speed();
	_quest_progress(y1, x1);
	x1 += pos.dx * time;
	y1 += pos.dy * time;

	if (checker.map_event(getRect1()) == false) {
		pos.xy.x = x1;
		pos.xy.y = y1;
	}

	properties.speed = 0;

	if (properties.health <= 0) {
		properties.life = false;
	}

	if (properties.life == false) {
		properties.health = 0;
	}
	sprite->setPosition(pos.xy.x, pos.xy.y);

}

FloatRect Player::getRect() {
	return FloatRect(pos.xy.x - properties.w / 2, pos.xy.y - properties.h / 2, properties.h, properties.w);
	std::cout << properties.h << std::endl;
}

FloatRect Player::getRect1() {
	return FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.h, properties.w);
}

float Player::getX() {
	return pos.xy.x;
}
float Player::getY() {
	return pos.xy.y;
}



bool Player::_map_event(float y1, float x1) {
	bool wall = 0;
	for (size_t i = 0; i < obj.size(); i++)
		if (getRect1().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid") {
				wall = true;
			}
		}
	return wall;
}

void Player::_quest_progress(float y1, float x1) {
	for (size_t i = 0; i < obj.size(); i++)//проходимся по объектам
		if (FloatRect(x1 - properties.w / 2, y1 - properties.h / 2, properties.h, properties.w).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "car" && quest == 0) {
				quest = 1;
			}
			else if (obj[i].name == "gaz" && quest == 1) {
				quest = 2;
			}
			else if (obj[i].name == "bucket" && quest == 2) {
				quest = 3;
			}
			else if (obj[i].name == "colon" && quest == 3) {
				quest = 4;
			}
			else if (obj[i].name == "car" && quest == 4) {
				quest = 5;
			}
		}
}