#include "Turtle.h"
#include <iostream>
#include <stdlib.h>

Turtle::Turtle() {
	this->setInitiative(0);
	this->setStrength(0);
	this->setSign('T');
	this->setWorld(nullptr);
	this->setAge(0);
}

Turtle::Turtle(World* world, vector<int> pos) {
	this->setInitiative(1);
	this->setStrength(2);
	this->setSign('T');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Turtle::Turtle(World* world, vector<int> pos, int strength, int age) {
	this->setInitiative(1);
	this->setStrength(strength);
	this->setSign('T');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

Turtle* Turtle::Reproduce(vector<int> pos) {
	Turtle* t = new Turtle(getWorld(), pos);
	return t;
}

//collider -> organism that attacked
void Turtle::Collision(Organism* collider) {
	if (this->Draw() != collider->Draw()) {
		if (collider->getStrength() < 5) {

			//event handler
			string log = "T defended himself from "; 
			log += collider->Draw();
			getWorld()->gameFeed(log);
			////////////////////////// 
			return;
		}
		else {
			if (collider->getStrength() >= this->getStrength()) {

				//event handler
				addFeed(collider, this);

				collider->setPosition(this->getPosition());
				getWorld()->killOrganism(this);
			}
			else {
				//event handler
				addFeed(this, collider);

				getWorld()->killOrganism(collider);
			}
		}
	}
	else {
		vector<int> new_pos = this->newPosition(this->getPosition());
		bool isSomethingThere = this->checkPosition(new_pos);

		if (this->checkIfSurrounded(this->getPosition()) == false) {
			if (!isSomethingThere) {
				getWorld()->addOrganism(this->Reproduce(new_pos));
			}
			//else this->Collision(collider);
		}
	}
}

void Turtle::Action() {
	if ((rand() % 100 + 1) > 75) {
		vector<int> pos = this->getPosition();

		vector<int> new_pos = this->newPosition(pos);
		Organism* isEmpty = this->checkField(new_pos);

		if (isEmpty == nullptr) this->setPosition(new_pos);
		else isEmpty->Collision(this);
	}
}