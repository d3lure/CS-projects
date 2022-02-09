#include "Antelope.h"
#include <iostream>

Antelope::Antelope() {
	this->setInitiative(4);
	this->setStrength(4);
	this->setSign('A');
	this->setWorld(nullptr);
}

Antelope::Antelope(World* world, vector<int> pos) {
	this->setInitiative(4);
	this->setStrength(4);
	this->setSign('A');
	this->setWorld(world);
	this->setPosition(pos);
}

Antelope::Antelope(World* world, vector<int> pos, int strength, int age) {
	this->setInitiative(4);
	this->setStrength(strength);
	this->setSign('A');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

Antelope* Antelope::Reproduce(vector<int> pos) {
	Antelope* a = new Antelope(this->getWorld(), pos);
	return a;
};

//collider -> organism that attacked
void Antelope::Collision(Organism* collider) {
	if (this->Draw() != collider->Draw()) {
		if (collider->getStrength() >= this->getStrength()) {
			if ((rand() % 2) == 0) {

				//event handler
				addFeed(collider, this);

				collider->setPosition(this->getPosition());
				getWorld()->killOrganism(this);
			}
			else {
				//event handler
				string log = "A has run away from ";
				log += collider->Draw();
				getWorld()->gameFeed(log);
				Action();
				///////////////
			}
		}
		else {
			//event handler
			addFeed(this, collider);
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

void Antelope::Action() {

	vector<int> pos = this->getPosition();
	vector<int> new_pos = this->newPosition(pos);
	Organism* isEmpty = this->checkField(new_pos);

	if (isEmpty == nullptr) this->setPosition(new_pos);
	else isEmpty->Collision(this);

}

vector<int> Antelope::newPosition(vector<int> pos) {
	vector<int> new_pos = pos;

	int prob = rand() % 2;
	int index = rand() % 2;
	int value = rand() % 2 + 1;

	if (prob == 0) new_pos[index] += value;
	else new_pos[index] += -value;

	if (new_pos[0] <= 0 || new_pos[0] >= (getWorld()->getX()) ||
		new_pos[1] <= 0 || new_pos[1] >= (getWorld()->getY())) {

		return newPosition(pos);
	}
	else return new_pos;
}