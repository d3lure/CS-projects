#pragma once
#include "Plant.h"

class Hogweed : public Plant {
	vector<Organism*> neighbourhood;
public:
	Hogweed();
	Hogweed(World *world, vector<int> pos);
	Hogweed(World* world, vector<int> pos, int age);
	~Hogweed();

	void Action() override;
	void Collision(Organism* collider) override;
	Hogweed* Reproduce(vector<int> pos);
	void setNeighbourhood();
	
};