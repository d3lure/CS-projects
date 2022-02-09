#include "Dandelion.h"

Dandelion::Dandelion() {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('*');
	this->setWorld(nullptr);
	this->setAge(0);
}

Dandelion::Dandelion(World* world, vector<int> pos) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('*');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Dandelion::Dandelion(World* world, vector<int> pos, int age) {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('*');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

void Dandelion::Action() {
	for (int i = 0; i < 3; i++) {
		if ((rand() % 100 + 1) < 20) {
			vector<int> pos = getPosition();
			if (this->checkIfSurrounded(pos) == false) {
				vector<int> new_pos = newPosition(pos);

				if (this->checkField(new_pos) == nullptr) {
					getWorld()->addOrganism(Reproduce(new_pos));
				}
				return;
				//else this->Action();
			}
		}
	}
}

Dandelion* Dandelion::Reproduce(vector<int> pos) {
	Dandelion* d = new Dandelion(getWorld(), pos);
	return d;
}