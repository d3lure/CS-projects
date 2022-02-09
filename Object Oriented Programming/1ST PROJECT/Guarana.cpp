#include "Guarana.h"
#include <iostream>

Guarana::Guarana() {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('+');
	this->setWorld(nullptr);
	this->setAge(0);
}

Guarana::Guarana(World* world, vector<int> pos) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('+');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Guarana::Guarana(World* world, vector<int> pos, int age) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('+');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

//collider -> organism that attacked
void Guarana::Collision(Organism* collider) {
	collider->setStrength(collider->getStrength() + 3);

	//event handler
	string log = "";
	log += collider->Draw();
	log += " eated guarana (+), its strength is now: ";
	log += to_string(collider->getStrength());
	getWorld()->gameFeed(log);
	//////////////////////////

	collider->setPosition(this->getPosition());
	getWorld()->killOrganism(this);
}

Guarana* Guarana::Reproduce(vector<int> pos) {
	Guarana* g = new Guarana(getWorld(), pos);
	return g;
}