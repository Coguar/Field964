#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "health.h"
#include <iostream>
#include <sstream>

void ShowHealth(RenderWindow & window, Text & text, int & health_value, View & view)
{
	std::ostringstream playerHealthString;    // �������� ����������
	playerHealthString << health_value;		//������� � ��� ����� ��������, �� ���� ��������� ������
	text.setString("��������:" + playerHealthString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
	text.setPosition(view.getCenter().x - 256, view.getCenter().y - 256);//������ ������� ������, �������� �� ������ ������
	window.draw(text);//����� ���� ����n
}