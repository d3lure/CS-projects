#include "Sheep.h"

Sheep::Sheep() {
	this->setAge(0);
	this->setInitiative(4);
	this->setSign('S');
	this->setStrength(4);
	this->setWorld(nullptr);
}

Sheep::Sheep(World* world, vector<int> pos) {
	this->setAge(0);
	this->setInitiative(4);
	this->setSign('S');
	this->setStrength(4);
	this->setPosition(pos);
	this->setWorld(world);
}

Sheep::Sheep(World* world, vector<int> pos, int strength, int age) {
	this->setAge(age);
	this->setInitiative(4);
	this->setSign('S');
	this->setStrength(strength);
	this->setPosition(pos);
	this->setWorld(world);
}

Sheep* Sheep::Reproduce(vector<int> pos) {
	Sheep* s = new Sheep(getWorld(), pos);
	return s;
}