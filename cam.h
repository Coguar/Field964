#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void getCoord(float x, float y, View & view1)
{ //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;

	if (x < view1.getSize().x / 2) tempX = view1.getSize().x / 2;
	if (x > 1600 - view1.getSize().x / 2) tempX = 1600 - view1.getSize().x / 2;//������� �� ���� ����� �������
	if (y < view1.getSize().y / 2) tempY = view1.getSize().y / 2;//������� �������
	if (y > 1600 - view1.getSize().y / 2) tempY = 1600 - view1.getSize().y / 2;

	view1.setCenter(tempX, tempY);
	//������ �� �������, ��������� ��� ����������. 
}