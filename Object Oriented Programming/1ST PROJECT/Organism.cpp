#include "Organism.h"
#include <iostream>
using namespace std;

//operator overloading
bool operator == (Organism& org1, Organism& org2) {
	if (
		org1.getStrength() == org2.getStrength() &&
		org1.getInitiative() == org2.getInitiative() &&
		org1.getPosition() == org2.getPosition()
		) return true;

	else return false;
}

void Organism::Action() {}
void Organism::Collision(Organism* collided) {}

Organism::Organism() {
	this->initiative = 0;
	this->strength = 0;
	this->sign = ' ';
	this->world = nullptr;
	this->age = 0;
}

Organism::~Organism() {
	delete world;
}

//GETTERS
World* Organism::getWorld() const {
	return this->world;
}
int Organism::getAge() const {
	return this->age;
}
vector<int> Organism::getPosition() const {
	return this->position;
}
int Organism::getStrength() const {
	return this->strength;
}
int Organism::getInitiative() const {
	return this->initiative;
}


//SETTERS
void Organism::setAge(int a) {
	this->age = a;
}
void Organism::setStrength(int str) {
	this->strength = str;
}
void Organism::setInitiative(int init) {
	this->initiative = init;
}
void Organism::setSign(char sign) {
	this->sign = sign;
}
void Organism::setPosition(vector<int> pos) {
	this->position = pos;
}
void Organism::setWorld(World* world) {
	this->world = world;
}


char Organism::Draw() {
	return this->sign;
}

void Organism::addFeed(Organism* w, Organism* l) {
	string log = "";
	log += w->Draw();
	log += " killed ";
	log += l->Draw();
	this->world->gameFeed(log);
}

//randomly pick new position which is
//one 'step' away from current position
//if new position is outside the world
//pick new one
vector<int> Organism::newPosition(vector<int> pos) {
	vector<int> new_pos = pos;

	int prob = rand() % 2;
	int index = rand() % 2;

	if (prob == 0) new_pos[index] += 1;
	else new_pos[index] += -1;

	if (new_pos[0] == 0 || new_pos[0] == (this->world->getX() ) ||
		new_pos[1] == 0 || new_pos[1] == (this->world->getY() )) {

		return newPosition(pos);
	}
	else return new_pos;
}

//checks if organism is surrounded by other organisms
bool Organism::checkIfSurrounded(vector<int> pos) {

	vector<vector<int>> positions;

	vector<int> pos1 = { pos[0] + 1, pos[1] };
	vector<int> pos2 = { pos[0] - 1, pos[1] };
	vector<int> pos3 = { pos[0], pos[1] + 1 };
	vector<int> pos4 = { pos[0], pos[1] - 1 };

	positions.push_back(pos1);
	positions.push_back(pos2);
	positions.push_back(pos3);
	positions.push_back(pos4);

	for (vector<int> pos : positions) {

		if (this->checkField(pos) == nullptr) return false;
	}
	return true;
}

//checks if something is on given position
//if true return this organism
Organism* Organism::checkField(vector<int> pos) {
	for (Organism* o : this->world->getOrganisms()) {
		if (o->getPosition() == pos) {
			//cout << "Collision Detected" << endl;
			return o;
		}
	}
	return nullptr;
}

//similar to above but return boolean values
//true if there is some organism
bool Organism::checkPosition(vector<int> pos) {
	for (Organism* o : this->world->getOrganisms()) {
		if (o->getPosition() == pos) {
			//cout << "Collision Detected" << endl;
			return true;
		}
	}
	return false;
}