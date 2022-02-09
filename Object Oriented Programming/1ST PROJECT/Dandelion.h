#pragma once
#include "Plant.h"

class Dandelion : public Plant {

public:
	Dandelion();
	Dandelion(World* world, vector<int> pos);
	Dandelion(World* world, vector<int> pos, int age);

	void Action() override;

	Dandelion* Reproduce(vector<int> pos);
};