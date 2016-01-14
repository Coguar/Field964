#include "stdafx.h"
#include "classCollisionChecker.h"

bool CollisionChecker::map_event(FloatRect & rect) {
	bool wall = false;
	for (size_t i = 0; i < obj.size(); i++)//���������� �� ��������
		if (rect.intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid") {
				wall = true;
			}
		}
	return wall;
}

bool CollisionChecker::quest_event(FloatRect & rect, std::string name) {
	bool wall = false;
	for (size_t i = 0; i < obj.size(); i++)//���������� �� ��������
		if (rect.intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == name) {
				wall = true;
			}
		}
	return wall;
}