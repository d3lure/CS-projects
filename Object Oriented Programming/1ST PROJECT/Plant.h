#pragma once
#include "Organism.h"

class Plant : public Organism {

public:
	Plant(World* world, int strength, char sign, vector<int> position);
	Plant();
	virtual void Action() override;
	virtual void Collision(Organism* collider) override;
};