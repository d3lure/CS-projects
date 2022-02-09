#include "Animal.h"
#include <iostream>
//#include <typeinfo>
#include <windows.h>

Animal::Animal(World* world, int strength, int initiative, char sign, vector<int> position) {

	this->setStrength(strength);
	this->setInitiative(initiative);
	this->setSign(sign);
	this->setPosition(position);
	this->setWorld(world);
	this->setAge(0);
}

Animal::Animal() {
	this->setStrength(0);
	this->setInitiative(0);
	this->setSign('#');
	this->setWorld(nullptr);
	this->setAge(0);
}

//collider -> organism that attacked
void Animal::Collision(Organism* collider) {
	if (this->Draw() != collider->Draw()) {
		if (collider->getStrength() >= this->getStrength()) {

			//event handler
			addFeed(collider, this);
			
			collider->setPosition(this->getPosition());
			getWorld()->killOrganism(this);
		}
		else {
			//event handler
			if (dynamic_cast<Animal*>(collider)) {
				addFeed(this, collider);
			} 
			getWorld()->killOrganism(collider);
		}
	}
	else {
		if (this->checkIfSurrounded(this->getPosition()) == false) {
			vector<int> new_pos = this->newPosition(this->getPosition());
			bool isSomethingThere = this->checkPosition(new_pos);
			if (!isSomethingThere) {
				getWorld()->addOrganism(Reproduce(new_pos));
			}
			//else this->Collision(collider);
		}
	}
}

void Animal::Action() {

	vector<int> pos = this->getPosition();
	vector<int> new_pos = this->newPosition(pos);
	Organism* isEmpty = this->checkField(new_pos);

	if (isEmpty == nullptr) this->setPosition(new_pos);
	else isEmpty->Collision(this);

}





