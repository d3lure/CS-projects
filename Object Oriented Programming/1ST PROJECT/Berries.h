#pragma once
#include "Plant.h"

class Berries : public Plant {
public:
	Berries();
	Berries(World* world, vector<int> pos);
	Berries(World* world, vector<int> pos, int age);

	Berries* Reproduce(vector<int> pos);
};