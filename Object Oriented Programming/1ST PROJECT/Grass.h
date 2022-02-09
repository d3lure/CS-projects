#pragma once
#include "Plant.h"

class Grass : public Plant {
public:
	Grass();
	Grass(World *world, vector<int> pos);
	Grass(World* world, vector<int> pos, int age);

	Grass* Reproduce(vector<int> pos);
};