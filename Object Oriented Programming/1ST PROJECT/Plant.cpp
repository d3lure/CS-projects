#include "Plant.h"
#include <ctime>
#include <iostream>
#include <vector>

Plant::Plant(World* world, int strength, char sign, vector<int> position) {

	this->setStrength(strength);
	this->setInitiative(0);
	this->setSign(sign);
	this->setPosition(position);
	this->setWorld(world);
	this->setAge(0);
}

Plant::Plant() {
	this->setInitiative(0);
	this->setStrength(0);
}

void Plant::Collision(Organism* collider) {
	if (this->Draw() != collider->Draw()) {
		if (collider->getStrength() >= this->getStrength()) {
			//I decided not to print this event, 
			//cause it occured too often
			collider->setPosition(this->getPosition());
			getWorld()->killOrganism(this);
		}
		else {
			//event handler
			addFeed(this, collider);

			getWorld()->killOrganism(this);
			getWorld()->killOrganism(collider);
		}
	}
}

//with given probability plant tries to reproduce
void Plant::Action() {

	if ((rand() % 100 + 1) < 20) {
		
		vector<int> pos = this->getPosition();

		if (this->checkIfSurrounded(pos) == false) {
			vector<int> new_pos = this->newPosition(pos);

			if (this->checkField(new_pos) == nullptr) {
				getWorld()->addOrganism(this->Reproduce(new_pos));
			}
			//else return this->Action();
		}
	}
}




