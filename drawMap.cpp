#include "stdafx.h"
#include "drawMap.h"
#include <iostream>
#include <sstream>
#include "map.h"

/*static TileType g_tiletype = TileType();

const int block_size = 32;

void draw(Game_window & game_window, float & res, float & time, String* TileMap, Sprite & s_map){

	for (int i = 0; i < game_window.heigth; i++)
		for (int j = 0; j < game_window.width; j++){
			if (TileMap[i][j] == g_tiletype.BOTTLE && time - res > 5) TileMap[i][j] = 'v';
			if (TileMap[i][j] == g_tiletype.FLOOR)  s_map.setTextureRect(IntRect(64, 0, block_size, block_size)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == g_tiletype.GRASS)  s_map.setTextureRect(IntRect(0, 0, block_size, block_size));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == g_tiletype.WALL)) s_map.setTextureRect(IntRect(32, 0, block_size, block_size));
			if ((TileMap[i][j] == g_tiletype.H_WINDOW)) s_map.setTextureRect(IntRect(96, 0, block_size, block_size));
			if ((TileMap[i][j] == g_tiletype.V_WINDOW)) s_map.setTextureRect(IntRect(128, 0, block_size, block_size));
			if ((TileMap[i][j] == g_tiletype.VINE)) s_map.setTextureRect(IntRect(0, 32, block_size, block_size));
			if ((TileMap[i][j] == g_tiletype.BOTTLE)){
				s_map.setTextureRect(IntRect(32, 32, block_size, block_size));
				res = time;
			}
			s_map.setPosition(float(j * block_size), float(i * block_size));
			game_window.window->draw(s_map);
		}
}*/