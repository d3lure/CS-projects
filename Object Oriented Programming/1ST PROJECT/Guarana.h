#pragma once
#include "Plant.h"

class Guarana : public Plant {
public:
	Guarana();
	Guarana(World* world, vector<int> pos);
	Guarana(World* world, vector<int> pos, int age);

	void Collision(Organism* collider) override;

	Guarana* Reproduce(vector<int> pos);
};