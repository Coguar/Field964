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
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);//������ ������� ������, �������� �� ������ ������
	window.draw(text);//����� ���� ����n
}

void ShowAmmo(RenderWindow & window, Text & text, int & ammo_value, View & view)
{
	std::ostringstream playerHealthString;    // �������� ����������
	playerHealthString << ammo_value;		//������� � ��� ����� ��������, �� ���� ��������� ������
	if (ammo_value == -1) {
		text.setString("�������: ������������");
	}
	else {
		text.setString("�������:" + playerHealthString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
	}
	text.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + 30);//������ ������� ������, �������� �� ������ ������
	window.draw(text);//����� ���� ����n
}