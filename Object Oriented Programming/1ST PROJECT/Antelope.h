#pragma once
#include "Animal.h"

class Antelope : public Animal {

public:
	Antelope();
	Antelope(World* world, vector<int> pos);
	Antelope(World* world, vector<int> pos, 
		int strength, int age);

	void Action() override;
	void Collision(Organism* collider) override;

	Antelope* Reproduce(vector<int> pos);

	vector<int> newPosition(vector<int> pos);};