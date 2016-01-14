#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <list>

struct MenuConfig {
	std::string imagelist = "./files/img/menu/list.png";
	std::string start_img = "./files/img/menu/hand.png";

	std::string text_font = "./files/fonts/birch111.ttf";
	std::string button_font = "./files/fonts/birch111.ttf";

};

struct MenuImg {
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
};

struct MenuText {
	std::string new_game = "Новая игра";
	const sf::Vector2f new_game_pos = {200, 200};
	sf::FloatRect new_game_rect;

	std::string continue_game = "Продолжить";
	const sf::Vector2f continue_game_pos = { 200, 160 };
	sf::FloatRect continue_game_rect;

	std::string about = "Об игре";
	const sf::Vector2f about_pos = { 200, 120 };
	sf::FloatRect about_rect;

	std::string back = "Назад";
	const sf::Vector2f back_pos = { 200, -200 };
	sf::FloatRect back_rect;

	std::string exit = "Выход";
	const sf::Vector2f exit_pos = { 200, 80 };
	sf::FloatRect exit_rect;

	std::string about_text = "Управление: \n Ходьба - \n W:A:S:D \n Выстрел - \n Mouse Left \n Смена оружия - \n Mouse Wheel \n Совет: \nБерегите патроны. \nНе стойте наместе";
	const sf::Vector2f about_text_pos = { 200, 250 };
};

struct MissionText {
	std::string start = "Я должен выбираться\n отсюда! \n Нужно найти \nкакой-нибудь\n транспорт \n или что-то вроде того.\n Может вертолет или, \n убежище.";
	std::string find_car = "Отлично! \nВот эта подойдет! \n Черт! Она не \nзаправлена, \nя должен найти заправку.\n Мне бы и самому \nзаправиться...\n Интересно, \nзомби вкусные?";
	std::string find_gaz = "А вот и заправка! \n Только вот канистры \nсовсем нигде нет.. \n Кто-то конкретно \nиздевается... \n Канистра, я иду!";
	std::string find_buscket = "О, вот это мне и нужно! \n Большая, крассная, почти новая канистра. \n Как мне повезло 'совершенно случайно' ее найти.";
	std::string find_colon = "Бегом заправляться! \n Эти твари мне \nпорядком надоели. \n Было бы лучше, \nесли бы это был Дом2 \n Кажется я где-то\n видел одного из \nучастников";
	std::string go_to_car = "Тяжелая зараза! \n Не могу быстро \nс ней бежать. \n Пришлось зажать ее \nмежду ног, чтобы \n держать оружие.";
};

struct MenuInfo
{
	sf::Font font;
	std::shared_ptr<sf::Text> text;
	int font_size = 30;
};

struct menuBools{
	bool change_music = false;
	bool menu = true;
	bool about = false;
	bool restart = false;
	bool exit = false;
	bool first_play = true;
};

