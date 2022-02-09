#pragma once
#include "Animal.h"

class Turtle : public Animal {


public:
	Turtle();
	Turtle(World* world, vector<int> pos);
	Turtle(World* world, vector<int> pos,
		int strength, int age);

	void Action() override;
	void Collision(Organism* collider) override;

	Turtle* Reproduce(vector<int> pos);

};