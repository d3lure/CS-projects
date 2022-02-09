#include "Berries.h"

Berries::Berries() {
	this->setInitiative(0);
	this->setStrength(99);
	this->setSign(':');
	this->setWorld(nullptr);
	this->setAge(0);
}

Berries::Berries(World* world, vector<int> pos) {
	this->setInitiative(0);
	this->setStrength(99);
	this->setSign(':');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Berries::Berries(World* world, vector<int> pos, int age) {
	this->setInitiative(0);
	this->setStrength(99);
	this->setSign(':');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

Berries* Berries::Reproduce(vector<int> pos) {
	Berries* b = new Berries(getWorld(), pos);
	return b;
}