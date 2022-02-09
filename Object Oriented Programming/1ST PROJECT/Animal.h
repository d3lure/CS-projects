#pragma once
#include "Organism.h"

class Animal : public Organism {
	
public:
	Animal(World *world, int strength, int initiative, 
		char sign, vector<int> position);
	Animal();

	virtual void Action();
	virtual void Collision(Organism* collider);

	virtual Animal* Reproduce(vector<int> pos)=0;

};