#pragma once
#include "Animal.h"
class Sheep : public Animal {
public:
	Sheep();
	Sheep(World* world, vector<int> pos);
	Sheep(World* world, vector<int> pos,
		int strength, int age);

	Sheep* Reproduce(vector<int> pos);
};