#include "stdafx.h"
#include "MenuStruct.h"
#include "GamesStruct.h"
#include "Menu.h"
#include "gameEvent.h"
#include "Initiation.h"

bool _select_button(sf::Vector2f pos, FloatRect & rect){
		if (FloatRect(pos.x, pos.y, 1, 1).intersects(rect)) {
			return true;
		}
		else 
		{
			return false;
		}
}

void _choose_color(sf::Text & text, sf::Vector2f pos, FloatRect & rect){
	if (_select_button(pos, rect)){
		text.setColor(Color::Yellow);
	}
	else {
		text.setColor(Color::Red);
	}
}

void showMenu(Game1 & game, MenuText & menu_text, sf::Text & text, MenuImg & fon, menuBools & bools)
{

	game.window->draw(*fon.sprite);
	if (!bools.about) {
		text.setString(menu_text.new_game);
		menu_text.new_game_rect = { fon.sprite->getPosition().x - menu_text.new_game_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.new_game_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		_choose_color(text, game.pos, menu_text.new_game_rect);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.new_game_pos.x, fon.sprite->getPosition().y - menu_text.new_game_pos.y);
		game.window->draw(text);

		text.setString(menu_text.continue_game);
		menu_text.continue_game_rect = { fon.sprite->getPosition().x - menu_text.continue_game_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.continue_game_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		if (bools.first_play) {
			text.setColor(Color(128, 128, 128));
		}
		else {
			_choose_color(text, game.pos, menu_text.continue_game_rect);
		}
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.continue_game_pos.x, fon.sprite->getPosition().y - menu_text.continue_game_pos.y);
		game.window->draw(text);

		text.setString(menu_text.about);
		menu_text.about_rect = { fon.sprite->getPosition().x - menu_text.about_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.about_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		_choose_color(text, game.pos, menu_text.about_rect);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.about_pos.x, fon.sprite->getPosition().y - menu_text.about_pos.y);
		game.window->draw(text);

		text.setString(menu_text.exit);
		menu_text.exit_rect = { fon.sprite->getPosition().x - menu_text.exit_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.exit_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		_choose_color(text, game.pos, menu_text.exit_rect);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.exit_pos.x, fon.sprite->getPosition().y - menu_text.exit_pos.y);
		game.window->draw(text);
	}
	else {
		text.setColor(Color::Red);
		text.setString(menu_text.about_text);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.about_text_pos.x, fon.sprite->getPosition().y - menu_text.about_text_pos.y);
		game.window->draw(text);

		text.setString(menu_text.back);
		menu_text.back_rect = { fon.sprite->getPosition().x - menu_text.back_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.back_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		_choose_color(text, game.pos, menu_text.back_rect);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.back_pos.x, fon.sprite->getPosition().y - menu_text.back_pos.y);
		game.window->draw(text);
	}
}

void initMenuFon(MenuConfig & config, MenuImg & fon) {
	fon.hand_texture = std::make_shared<sf::Texture>();
	fon.hand_texture->loadFromFile(config.start_img);
	fon.hand_sprite = std::make_shared<sf::Sprite>();
	fon.hand_sprite->setTexture(*fon.hand_texture);
	fon.hand_sprite->setOrigin(fon.hand_texture->getSize().x / 2, fon.hand_texture->getSize().y / 2);
	fon.hand_sprite->setPosition(600, 300);

	sf::Image image;
	image.loadFromFile(config.imagelist);
	fon.texture = std::make_shared<sf::Texture>();
	fon.texture->loadFromImage(image);
	fon.sprite = std::make_shared<sf::Sprite>();
	fon.sprite->setTexture(*fon.texture);
	fon.sprite->setOrigin(400, 300);
	fon.sprite->setPosition(400, 300);
}

void initMenuText(MenuConfig & config, MenuInfo & menu_info)
{

	menu_info.font.loadFromFile(config.button_font);
	menu_info.text = std::make_shared<sf::Text>("", menu_info.font, menu_info.font_size);
	menu_info.text->setColor(sf::Color::Red);
	menu_info.text->setStyle(sf::Text::Bold);
}

void showMission(Game1 & game, MissionText & mission_text, sf::Text & text, Hero & hero, MenuImg & fon, menuBools & bools)
{
	if (!bools.first_play) {
		switch (hero.player->quest)
		{
		case Player::quest_status::start: text.setString(mission_text.start); break;
		case Player::quest_status::find_car: text.setString(mission_text.find_car); break;
		case Player::quest_status::find_gaz: text.setString(mission_text.find_gaz); break;
		case Player::quest_status::find_busket: text.setString(mission_text.find_buscket); break;
		case Player::quest_status::find_colon: text.setString(mission_text.find_colon); break;
		case Player::quest_status::go_to_car: text.setString(mission_text.go_to_car); break;
		}
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x + 220, fon.sprite->getPosition().y - 250);
		text.setColor(Color::Red);
		game.window->draw(text);
	}
	else {
		fon.hand_sprite->setPosition(fon.sprite->getPosition().x + 200, fon.sprite->getPosition().y);
		game.window->draw(*fon.hand_sprite);

	}
	game.aim_sprite->setPosition(game.pos);
	game.window->draw(*game.aim_sprite);
	game.window->display();
}

void clickedButton(menuBools & bools, MenuText & menu_text, sf::Vector2f pos) {
	if (!bools.about) {
		if (FloatRect(pos.x, pos.y, 1, 1).intersects(menu_text.new_game_rect)) {
			bools.restart = true;
			bools.change_music = true;
		}
		else if (FloatRect(pos.x, pos.y, 1, 1).intersects(menu_text.continue_game_rect) && !bools.first_play) {
			bools.menu = !bools.menu;
			bools.change_music = true;
		}
		else if (FloatRect(pos.x, pos.y, 1, 1).intersects(menu_text.about_rect)) {
			bools.about = true;
		}
		else if (FloatRect(pos.x, pos.y, 1, 1).intersects(menu_text.exit_rect)) {
			bools.exit = true;
		}
	}
	else {
		if (FloatRect(pos.x, pos.y, 1, 1).intersects(menu_text.back_rect)) {
			bools.about = false;
		}
	}
}

void restartGame(menuBools & bools, std::shared_ptr<Lists> lists, Game1 & game, Monster & enemy, Hero & hero, Config & config) {
	if (bools.restart) {
		lists.reset();
		lists = std::make_shared<Lists>();
		eventPushLists(config, std::ref(*lists), game, enemy);
		GameReInit(config, game, hero);
		bools.menu = false;
		bools.restart = false;
		bools.first_play = false;

	}
}