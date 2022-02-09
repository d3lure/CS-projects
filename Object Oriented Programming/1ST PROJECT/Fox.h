#pragma once
#include "Animal.h"

class Fox : public Animal {


public:
	Fox();
	Fox(World* world, vector<int> pos);
	Fox(World* world, vector<int> pos, 
		int strength, int age);

	void Action() override;
	Fox* Reproduce(vector<int> pos) override;
};