#pragma once

void showMenu(Game1 & game, MenuText & menu_text, sf::Text & text, MenuImg & fon, menuBools & bools);

void initMenuFon(MenuConfig & config, MenuImg & fon);

void initMenuText(MenuConfig & config, MenuInfo & menu_info);

void showMission(Game1 & game, MissionText & mission_text, sf::Text & text, Hero & hero, MenuImg & fon, menuBools & bools);

void clickedButton(menuBools & bools, MenuText & menu_text, sf::Vector2f pos);

void restartGame(menuBools & bools, std::shared_ptr<Lists> lists, Game1 & game, Monster & enemy, Hero & hero, Config & config);
