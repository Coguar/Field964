#include "stdafx.h"
#include "MenuStruct.h"
#include "GamesStruct.h"
#include "Menu.h"

void showMenu(sf::RenderWindow & window, MenuText & menu_text, sf::Text & text, MenuImg & fon, menuBools & bools)
{

	window.draw(*fon.sprite);
	if (!bools.about) {
		text.setString(menu_text.new_game);
		menu_text.new_game_rect = { fon.sprite->getPosition().x - menu_text.new_game_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.new_game_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.new_game_pos.x, fon.sprite->getPosition().y - menu_text.new_game_pos.y);
		window.draw(text);

		text.setString(menu_text.continue_game);
		menu_text.continue_game_rect = { fon.sprite->getPosition().x - menu_text.continue_game_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.continue_game_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.continue_game_pos.x, fon.sprite->getPosition().y - menu_text.continue_game_pos.y);
		window.draw(text);

		text.setString(menu_text.about);
		menu_text.about_rect = { fon.sprite->getPosition().x - menu_text.about_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.about_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.about_pos.x, fon.sprite->getPosition().y - menu_text.about_pos.y);
		window.draw(text);

		text.setString(menu_text.exit);
		menu_text.exit_rect = { fon.sprite->getPosition().x - menu_text.exit_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.exit_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.exit_pos.x, fon.sprite->getPosition().y - menu_text.exit_pos.y);
		window.draw(text);
	}
	else {
		text.setString(menu_text.about_text);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.about_text_pos.x, fon.sprite->getPosition().y - menu_text.about_text_pos.y);
		window.draw(text);

		text.setString(menu_text.back);
		menu_text.back_rect = { fon.sprite->getPosition().x - menu_text.back_pos.x - text.getLocalBounds().width / 2, fon.sprite->getPosition().y - menu_text.back_pos.y, text.getLocalBounds().width, text.getLocalBounds().height };
		text.setOrigin(text.getLocalBounds().width / 2, 0);
		text.setPosition(fon.sprite->getPosition().x - menu_text.back_pos.x, fon.sprite->getPosition().y - menu_text.back_pos.y);
		window.draw(text);
	}
	//window.display();
}

void initMenuFon(MenuConfig & config, MenuImg & fon) {
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

void showMission(sf::RenderWindow & window, MissionText & mission_text, sf::Text & text, Hero & hero, MenuImg & fon)
{
	switch (hero.player->quest)
	{
	case Player::quest_status::start: text.setString(mission_text.start); break;
	case Player::quest_status::find_car: text.setString(mission_text.find_car); break;
	case Player::quest_status::find_gaz: text.setString(mission_text.find_gaz); break;
	case Player::quest_status::find_busket: text.setString(mission_text.find_buscket); break;
	case Player::quest_status::find_colon: text.setString(mission_text.find_colon); break;
	case Player::quest_status::go_to_car: text.setString(mission_text.go_to_car); break;
	}
	//text.setCharacterSize();
	text.setOrigin(text.getLocalBounds().width / 2, 0);
	text.setPosition(fon.sprite->getPosition().x + 220, fon.sprite->getPosition().y - 250);
	window.draw(text);
	window.display();
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