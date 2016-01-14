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
	std::string new_game = "����� ����";
	const sf::Vector2f new_game_pos = {200, 200};
	sf::FloatRect new_game_rect;

	std::string continue_game = "����������";
	const sf::Vector2f continue_game_pos = { 200, 160 };
	sf::FloatRect continue_game_rect;

	std::string about = "�� ����";
	const sf::Vector2f about_pos = { 200, 120 };
	sf::FloatRect about_rect;

	std::string back = "�����";
	const sf::Vector2f back_pos = { 200, -200 };
	sf::FloatRect back_rect;

	std::string exit = "�����";
	const sf::Vector2f exit_pos = { 200, 80 };
	sf::FloatRect exit_rect;

	std::string about_text = "����������: \n ������ - \n W:A:S:D \n ������� - \n Mouse Left \n ����� ������ - \n Mouse Wheel \n �����: \n�������� �������. \n�� ������ �������";
	const sf::Vector2f about_text_pos = { 200, 250 };
};

struct MissionText {
	std::string start = "� ������ ����������\n ������! \n ����� ����� \n�����-������\n ��������� \n ��� ���-�� ����� ����.\n ����� �������� ���, \n �������.";
	std::string find_car = "�������! \n��� ��� ��������! \n ����! ��� �� \n����������, \n� ������ ����� ��������.\n ��� �� � ������ \n�����������...\n ���������, \n����� �������?";
	std::string find_gaz = "� ��� � ��������! \n ������ ��� �������� \n������ ����� ���.. \n ���-�� ��������� \n����������... \n ��������, � ���!";
	std::string find_buscket = "�, ��� ��� ��� � �����! \n �������, ��������, ����� ����� ��������. \n ��� ��� ������� '���������� ��������' �� �����.";
	std::string find_colon = "����� ������������! \n ��� ����� ��� \n�������� �������. \n ���� �� �����, \n���� �� ��� ��� ���2 \n ������� � ���-��\n ����� ������ �� \n����������";
	std::string go_to_car = "������� ������! \n �� ���� ������ \n� ��� ������. \n �������� ������ �� \n����� ���, ����� \n ������� ������.";
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

