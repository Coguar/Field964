#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void controlPlayer(Sprite & sprite, int & dir, float & speed, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down, int w);
