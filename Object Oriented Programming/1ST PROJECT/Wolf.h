#pragma once
#include "Animal.h"

class Wolf : public Animal {
public:
	Wolf();
	Wolf(World* world, vector<int> pos);
	Wolf(World* world, vector<int> pos,
		int strength, int age);

	Wolf* Reproduce(vector<int> pos);
};