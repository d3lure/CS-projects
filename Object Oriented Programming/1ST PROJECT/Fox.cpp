#include "Fox.h"
#include <iostream>

Fox::Fox() {
	this->setInitiative(7);
	this->setStrength(3);
	this->setSign('F');
	this->setWorld(nullptr);
	this->setAge(0);
}

Fox::Fox(World* world, vector<int> pos) {
	this->setInitiative(7);
	this->setStrength(3);
	this->setSign('F');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Fox::Fox(World* world, vector<int> pos, int strength, int age) {
	this->setInitiative(7);
	this->setStrength(strength);
	this->setSign('F');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

void Fox::Action() {

	vector<int> pos = this->getPosition();
	vector<int> new_pos = this->newPosition(pos);
	Organism* isEmpty = this->checkField(new_pos);
	if (isEmpty == nullptr) this->setPosition(new_pos);

	//fox checks if opponent is stronger than him
	else if (isEmpty->getStrength() > this->getStrength()) {

		//event handler
		string log = "F decided not to fight with ";
		log += isEmpty->Draw();
		getWorld()->gameFeed(log);
		//////////////////////////
		
		//return this->Action();
	} 
	else isEmpty->Collision(this);

}

Fox* Fox::Reproduce(vector<int> pos) {
	Fox* f = new Fox(this->getWorld(), pos);
	return f;
};