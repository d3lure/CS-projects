#include "Grass.h"

Grass::Grass() {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('"');
	this->setWorld(nullptr);
	this->setAge(0);
}

Grass::Grass(World* world, vector<int> pos) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('"');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Grass::Grass(World* world, vector<int> pos, int age) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('"');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

Grass* Grass::Reproduce(vector<int> pos) {
	Grass* g = new Grass(getWorld(), pos);
	return g;
}