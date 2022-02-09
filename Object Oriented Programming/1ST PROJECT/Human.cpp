#include "Human.h"
#include <iostream>
#include <string>

Human::Human() {
	this->setAge(1);
	this->setInitiative(4);
	this->setSign('H');
	this->setStrength(5);
	this->setWorld(nullptr);
	this->countRounds = 0;
	this->timeout = 0;
	this->isImmortal = false;
}

Human::Human(World* world, vector<int> pos) {
	this->setAge(1);
	this->setInitiative(4);
	this->setSign('H');
	this->setStrength(5);
	this->setPosition(pos);
	this->setWorld(world);
	this->timeout = 0;
	this->countRounds = 0;
	this->isImmortal = false;
}

Human::Human(World* world, vector<int> pos, int strength, int age) {
	this->setAge(age);
	this->setInitiative(4);
	this->setSign('H');
	this->setStrength(strength);
	this->setPosition(pos);
	this->setWorld(world);
	this->timeout = 0;
	this->countRounds = 0;
	this->isImmortal = false;
}

Human::~Human() {
	getWorld()->setHuman(nullptr);
	delete getWorld();
}

Human* Human::Reproduce(vector<int> pos) {
	return this;
}

bool Human::getStateOfAbility() {
	if (isImmortal) return true;
	else return false;
}

int Human::getCountRounds() {
	return countRounds;
}

int Human::getTimeout() {
	return timeout;
}

void Human::setTimeout(int t) {
	this->timeout = t;
}

void Human::setCountRounds(int c) {
	this->countRounds = c;
}

//collider -> organism that attacked
void Human::Collision(Organism* collider) {
	if (isImmortal != true) {
		if (collider->getStrength() >= this->getStrength()) {
			//event handler
			addFeed(collider, this);
			collider->setPosition(this->getPosition());
			getWorld()->killOrganism(this);
			getWorld()->setHuman(nullptr);
		}
		else {
			//event handler
			addFeed(this, collider);
			getWorld()->killOrganism(collider);
		} 
	}
}

void Human::Action() {
	
	vector<int> curr_pos = this->getPosition();
	vector<int> new_pos = {0, 0};

	//init new position depends on arrow that was pressed
	if (getWorld()->getDirection() == 'u') new_pos = { curr_pos[0], curr_pos[1] - 1 };
	else if (getWorld()->getDirection() == 'd') new_pos = { curr_pos[0], curr_pos[1] + 1 };
	else if (getWorld()->getDirection() == 'l') new_pos = { curr_pos[0] - 1, curr_pos[1] };
	else if (getWorld()->getDirection() == 'r') new_pos = { curr_pos[0] + 1, curr_pos[1] };

	//if new position is not outside the world
	if (new_pos[0] != 0 && new_pos[1] != 0 
		&& new_pos[0] != getWorld()->getX() && new_pos[1] != getWorld()->getY()) {

		Organism* isEmpty = this->checkField(new_pos);
		if (isEmpty == nullptr) this->setPosition(new_pos);
		else if (isImmortal && isEmpty != nullptr) {
			if (isEmpty->getStrength() > this->getStrength()) {
				this->setPosition(newPosition(getPosition()));
			}
			else isEmpty->Collision(this);
		}
		else {
			if (isEmpty->getStrength() > this->getStrength()) {
				getWorld()->setHuman(nullptr);
			}
			isEmpty->Collision(this);
		}

	} //if it is outside the world, don't change position
	else this->setPosition(curr_pos);

	//countRounds -> rounds since activating ability
	//timeout -> when ability can be activated again
	if (isImmortal) {
		if (countRounds >= 5) {
			isImmortal = false;
			timeout = 5;
		}
		countRounds++;
	}
	else if (isImmortal == false && timeout > 0) {
		timeout--;
	}
}

void Human::Immortality() {
	if (isImmortal == false && timeout <= 0) {
		isImmortal = true;
		countRounds = 0;
	}
}

bool Human::checkIfImmortal() {
	return isImmortal;
}

//if (isImmortal) {
//}
//else if (isImmortal == false && timeout > 0) {
//	//cout << " not yet, rounds left: " << timeout << endl;
//}

//if (isImmortal) {
//	string log = "Immortality round: ";
//	log += to_string(countRounds);
//	this->world->gameFeed(log);
//}
//else if (!isImmortal) {
//	string log = "Rounds left to ability: ";
//	log += to_string(timeout);
//	this->world->gameFeed(log);
//}