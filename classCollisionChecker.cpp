#include "stdafx.h"
#include "classCollisionChecker.h"

bool CollisionChecker::map_event(FloatRect & rect) {
	bool wall = false;
	for (size_t i = 0; i < obj.size(); i++)//проходимся по объектам
		if (rect.intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid") {
				wall = true;
			}
		}
	return wall;
}