#include "stdafx.h"
#include <cstdlib> 
#include <random>
#include "randomValue.h"

int random_number(int number) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 32700); // 
	int random_number = dist(gen) % number;
	return random_number;
}