#include "Wolf.h"
#include <iostream>

Wolf::Wolf() {
	this->setStrength(9);
	this->setInitiative(5);
	this->setSign('W');
	this->setAge(0);
	this->setWorld(nullptr);
}

Wolf::Wolf(World* world, vector<int> pos) {
	this->setStrength(9);
	this->setInitiative(5);
	this->setSign('W');
	this->setAge(0);
	this->setWorld(world);
	this->setPosition(pos);
}

Wolf::Wolf(World* world, vector<int> pos, int strength, int age) {
	this->setStrength(strength);
	this->setInitiative(5);
	this->setSign('W');
	this->setAge(age);
	this->setWorld(world);
	this->setPosition(pos);
}

Wolf* Wolf::Reproduce(vector<int> pos) {
	Wolf* w = new Wolf(getWorld(), pos);
	return w;
}