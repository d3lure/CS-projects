#include "Hogweed.h"
#include "Animal.h"
#include "Human.h"
#include <vector>
#include <iostream>

Hogweed::Hogweed() {
	this->setInitiative(0);
	this->setStrength(10);
	this->setSign('!');
	this->setWorld(nullptr);
	this->setAge(0);
}

Hogweed::Hogweed(World* world, vector<int> pos) {
	this->setInitiative(0);
	this->setStrength(10);
	this->setSign('!');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(0);
}

Hogweed::Hogweed(World* world, vector<int> pos, int age) {
	this->setInitiative(0);
	this->setStrength(10);
	this->setSign('!');
	this->setWorld(world);
	this->setPosition(pos);
	this->setAge(age);
}

Hogweed::~Hogweed() {
	delete getWorld();
	delete &neighbourhood;
}

//checks what organisms are around hogweed
//and keeps them in 'neighbourhood'
void Hogweed::setNeighbourhood() {

	neighbourhood.clear();
	vector<int> curr_pos = this->getPosition();
	vector<vector<int>> positions;

	vector<int> pos1 = { curr_pos[0] + 1, curr_pos[1] };
	vector<int> pos2 = { curr_pos[0] - 1, curr_pos[1] };
	vector<int> pos3 = { curr_pos[0], curr_pos[1] + 1 };
	vector<int> pos4 = { curr_pos[0], curr_pos[1] - 1 };

	positions.push_back(pos1);
	positions.push_back(pos2);
	positions.push_back(pos3);
	positions.push_back(pos4);

	for (vector<int> pos : positions) {
		if (checkField(pos) != nullptr) {
			neighbourhood.push_back(checkField(pos));
		}
	}
}

void Hogweed::Action() {
	this->setNeighbourhood();
	for (int i = 0; i < neighbourhood.size(); i++) {

		//hogweed kills only animals so it checks if 
		//object inherits from Animal class
		if (dynamic_cast<Animal*>(neighbourhood[i])) {

			//there can be situation where human 
			//is immortal so hogweed has to omit him
			if (!dynamic_cast<Human*>(neighbourhood[i])) {
				addFeed(this, neighbourhood[i]);
				getWorld()->killOrganism(neighbourhood[i]);
				neighbourhood.erase(neighbourhood.begin() + i);
			}
			else {
				if (!getWorld()->getHuman()->checkIfImmortal()) {
					getWorld()->setHuman(nullptr);
					addFeed(this, neighbourhood[i]);
					getWorld()->killOrganism(neighbourhood[i]);
					neighbourhood.erase(neighbourhood.begin() + i);
				}
			}
		}
	}
	//lowered probability of reproducing
	if ((rand() % 100 + 1) < 5) {
		vector<int> pos = this->getPosition();
		if (this->checkIfSurrounded(pos) == false) {
			vector<int> new_pos = this->newPosition(pos);

			if (this->checkField(new_pos) == nullptr) {
				getWorld()->addOrganism(this->Reproduce(new_pos));
			}
			//else this->Action();
		}
	}
}

//collider -> organism that attacked
void Hogweed::Collision(Organism* collider) {
	if (this->Draw() != collider->Draw()) {
		if (collider->getStrength() >= this->getStrength()) {
			//event handler
			string log = "";
			log += collider->Draw();
			log += " managed to kill hogweed (!), but it is now dead";
			getWorld()->gameFeed(log);
			////////////////////
		}
		else {
			if (!dynamic_cast<Animal*>(collider) || 
				getWorld()->getHuman()->checkIfImmortal() != true) {

				//event handler
				addFeed(this, collider);
				getWorld()->killOrganism(collider);
			}
			else collider->setPosition(this->getPosition());
		}
		getWorld()->killOrganism(this);
	}
}

Hogweed* Hogweed::Reproduce(vector<int> pos) {
	Hogweed* h = new Hogweed(getWorld(), pos);
	return h;
}

