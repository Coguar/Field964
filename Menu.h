#pragma once

void showMenu(sf::RenderWindow & window, MenuText & menu_text, sf::Text & text, MenuImg & fon, menuBools & bools);

void initMenuFon(MenuConfig & config, MenuImg & fon);

void initMenuText(MenuConfig & config, MenuInfo & menu_info);

void showMission(sf::RenderWindow & window, MissionText & mission_text, sf::Text & text, Hero & hero, MenuImg & fon);

void clickedButton(menuBools & bools, MenuText & menu_text, sf::Vector2f pos);