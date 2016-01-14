#pragma once
#include "classGlobal.h"

using namespace sf;

class CollisionChecker {
public:
	std::vector<Object> obj;//вектор объектов карты
	CollisionChecker(std::shared_ptr<Level> lvl) {
		obj = lvl->GetAllObjects();
	}

	bool map_event(FloatRect & rect);

	bool quest_event(FloatRect & rect, std::string name);
};