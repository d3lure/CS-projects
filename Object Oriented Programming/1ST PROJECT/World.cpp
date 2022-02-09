#include "World.h"
#include "Sheep.h"
#include "Grass.h"
#include "Wolf.h"
#include "Fox.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Turtle.h"
#include "Berries.h"
#include "Antelope.h"
#include "Hogweed.h"
#include "Human.h"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <fstream>

World::World(int sX, int sY) {
	this->sX = sX;
	this->sY = sY;
	this->round = 0;
	this->human = nullptr;
	this->humanDirection = NULL;
}
World::World() {
	this->sX = 0;
	this->sY = 0;
	this->round = 0;
	this->human = nullptr;
	this->humanDirection = NULL;
}
World::~World() {
	for (Organism* o : this->getOrganisms()) {
		delete o;
	}
}

//SETTERS
void World::setDirection(char d) {
	this->humanDirection = d;
}
void World::setX(int x) {
	this->sX = x;
}
void World::setY(int y) {
	this->sY = y;
}
void World::setHuman(Human* h) {
	this->human = h;
}

//GETTERS
int World::getRound() const {
	return this->round;
}
int World::getX() const {
	return this->sX;
}
int World::getY() const {
	return this->sY;
}
vector<Organism*> World::getOrganisms() const {
	return this->organisms;
}
Organism* World::getOrganism(int index) const {
	return this->organisms[index];
}
char World::getDirection() const {
	return humanDirection;
}
Human* World::getHuman() {
	if( human != nullptr) return human;
}

//sorting organisms by initiative using sort() & lambda function
void World::sortOrganisms() {
	sort(organisms.begin(), organisms.end(), 
		[](const Organism* org1, const Organism* org2) {
			if (org1->getInitiative() == org2->getInitiative() && 
				(org1->getInitiative() != 0 && org2->getInitiative() != 0)) {
				return org1->getAge() > org2->getAge();
			}
			else return org1->getInitiative() > org2->getInitiative();
		});
}

//copy all organisms to tmp vector,
//because organisms' actions can influence
//the number of organisms which can lead to some errors
void World::makeRound() {
	this->sortOrganisms();
	vector<Organism*> tmp;
	tmp = this->organisms;

	//for each organism make action
	for (Organism* o : tmp) {
		o->Action();
		o->setAge(o->getAge() + 1);
	} 
	this->round += 1;
	this->printWorld();
}

void World::printWorld() {
	vector<int> currPos = {0, 0};
	for (int y = 0; y <= this->sY; y++) {
		for (int x = 0; x <= this->sX; x++) {
			currPos[0] = x;
			currPos[1] = y;
			if (x == 0 || y == 0 || x==sX || y==sY) {
				cout << "#";
			}
			else {
				bool isSomethingThere = false;
				for (Organism* o : this->organisms) {
					if (o->getPosition() == currPos) {
						cout << o->Draw();
						isSomethingThere = true;
						break;
					}
				}
				if (!isSomethingThere) cout << " ";
			}
		}
		cout << endl;
	}
	//print events 
	cout << endl << "Round: " << round << " | ";
	cout << getStateOfAbility() << endl;
	for (int i = 0; i <= sX; i++) cout << "-";
	cout << endl << feed;
	this->feed = "";
}

string World::getStateOfAbility() {
	if (human != nullptr) {
		bool ability = this->getHuman()->getStateOfAbility();
		if (ability) {
			string log = "Immortality round: ";
			log += to_string(this->getHuman()->getCountRounds());
			return log;
		}
		else {
			string log = "Rounds left to ability: ";
			log += to_string(this->getHuman()->getTimeout());
			return log;
		}
	}
	else {
		return "Human is dead";
	}
}

int World::numOfOrganisms() {
	return this->organisms.size();
}

void World::addOrganism(Organism* org) {
	this->organisms.push_back(org);	
}

void World::killOrganism(Organism* org) {
	organisms.erase(remove(organisms.begin(), organisms.end(), org), organisms.end());
}

void World::gameFeed(string log) {
	this->feed += (log+"\n");
}

//random world constructor
World::World(int sX, int sY, int n) {

	this->sX = sX;
	this->sY = sY;
	this->round = 0;

	Human* h = new Human(this, { rand() % (sX - 1) + 1, rand() % (sY - 1) + 1 });
	this->human = h;
	addOrganism(h);

	for (int i = 0; i < n; i++) {
		vector<int> pos = { rand() % (sX - 1) + 1, rand() % (sY - 1) + 1 };
		switch (rand() % 10 + 1) {
			case 1: {
				Wolf* org = new Wolf(this, pos);
				this->addOrganism(org);
				break;
			}
			case 2: {
				Sheep* org = new Sheep(this, pos);
				this->addOrganism(org);
				break;
			}
			case 3: {
				Fox* org = new Fox(this, pos);
				this->addOrganism(org);
				break;
			}
			case 4: {
				Turtle* org = new Turtle(this, pos);
				this->addOrganism(org);
				break;
			}
			case 5: {
				Grass* org = new Grass(this, pos);
				this->addOrganism(org);
				break;
			}
			case 6: {
				Guarana* org = new Guarana(this, pos);
				this->addOrganism(org);
				break;
			}
			case 7: {
				Dandelion* org = new Dandelion(this, pos);
				this->addOrganism(org);
				break;
			}
			case 8: {
				Berries* org = new Berries(this, pos);
				this->addOrganism(org);
				break;
			}
			case 9: {
				Antelope* org = new Antelope(this, pos);
				this->addOrganism(org);
				break;
			}
			case 10: {
				Hogweed* org = new Hogweed(this, pos);
				this->addOrganism(org);
				break;
			}

		}
	}
}

void World::escAnimation() {
	system("CLS");
	cout << "Saving game";
	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(500);
	}
}

void World::addOrganism(char sign, vector<int> pos, int strength, int age) {
	switch (sign) {
	case 'W': {
		Wolf* org = new Wolf(this, pos, strength, age);
		this->addOrganism(org);
		break;
	}
	case 'S': {
		Sheep* org = new Sheep(this, pos, strength, age);
		this->addOrganism(org);
		break;
	}
	case 'F': {
		Fox* org = new Fox(this, pos, strength, age);
		this->addOrganism(org);
		break;
	}
	case 'T': {
		Turtle* org = new Turtle(this, pos, strength, age);
		this->addOrganism(org);
		break;
	}
	case '"': {
		Grass* org = new Grass(this, pos, age);
		this->addOrganism(org);
		break;
	}
	case '+': {
		Guarana* org = new Guarana(this, pos, age);
		this->addOrganism(org);
		break;
	}
	case '*': {
		Dandelion* org = new Dandelion(this, pos, age);
		this->addOrganism(org);
		break;
	}
	case ':': {
		Berries* org = new Berries(this, pos, age);
		this->addOrganism(org);
		break;
	}
	case 'A': {
		Antelope* org = new Antelope(this, pos, strength, age);
		this->addOrganism(org);
		break;
	}
	case '!': {
		Hogweed* org = new Hogweed(this, pos, age);
		this->addOrganism(org);
		break;
	}
	case 'H': {
		Human* org = new Human(this, pos, strength, age);
		this->human = org;
		this->addOrganism(org);
		break;
	}
	}
}

void World::addOrganism(char sign, vector<int> pos) {
	switch (sign) {
		case 'W': {
			Wolf* org = new Wolf(this, pos);
			this->addOrganism(org);
			break;
		}
		case 'S': {
			Sheep* org = new Sheep(this, pos);
			this->addOrganism(org);
			break;
		}
		case 'F': {
			Fox* org = new Fox(this, pos);
			this->addOrganism(org);
			break;
		}
		case 'T': {
			Turtle* org = new Turtle(this, pos);
			this->addOrganism(org);
			break;
		}
		case '"': {
			Grass* org = new Grass(this, pos);
			this->addOrganism(org);
			break;
		}
		case '+': {
			Guarana* org = new Guarana(this, pos);
			this->addOrganism(org);
			break;
		}
		case '*': {
			Dandelion* org = new Dandelion(this, pos);
			this->addOrganism(org);
			break;
		}
		case ':': {
			Berries* org = new Berries(this, pos);
			this->addOrganism(org);
			break;
		}
		case 'A': {
			Antelope* org = new Antelope(this, pos);
			this->addOrganism(org);
			break;
		}
		case '!': {
			Hogweed* org = new Hogweed(this, pos);
			this->addOrganism(org);
			break;
		}
		case 'H': {
			Human* org = new Human(this, pos);
			this->human = org;
			this->addOrganism(org);
			break;
		}
	}
}

//saves the world graphicly
//(organisms' values are not preserved)
void World::saveToFile_1() {
	ofstream file("game_state.txt");
	if (file.is_open()) {
		vector<int> currPos = { 0, 0 };
		for (int y = 0; y <= this->sY; y++) {
			for (int x = 0; x <= this->sX; x++) {
				currPos = { x , y };
				if (x == 0 || y == 0 || x == sX || y == sY) {
					file << "#";
				}
				else {
					bool isSomethingThere = false;
					for (Organism* o : this->organisms) {
						if (o->getPosition() == currPos) {
							file << o->Draw();
							isSomethingThere = true;
							break;
						}
					}
					if (!isSomethingThere) file << " ";
				}
			}
			file << endl;
		}
		file.close();
	}
	else cout << "error" << endl;
}

//this one reads the world graphicly
World* World::readGameStateFromFile_1() {
	bool wasHuman = false;
	string line;
	vector<int> curr_pos;
	ifstream input("game_state.txt");
	if (!input.is_open()) {
		cout << "Couldn't open the file"<< endl;
	}
	else {
		int y = 0;
		while (getline(input, line)) {
			this->setX(line.size() - 1);

			for (int x = 0; x <= sX; x++) {
				curr_pos = { x , y };
				if (line[x] != ' ' || line[x] != '#') {
					if (line[x] == 'H') wasHuman = true;
					addOrganism(line[x], curr_pos);
				}
			}
			y++;
		}
		this->setY(y - 1);
		if (wasHuman == false) this->human = nullptr;
	}
	return this;
}

void World::saveToFile_2() {
	ofstream output("game_state2.txt");
	if (output.is_open()) {
		//dimensions of the world
		output << sX << "%" << sY << "%" << round << "%" << endl;
		for (int i= 0; i < organisms.size() - 1; i++) {
			Organism* org = organisms[i];
			//organisms[i]->Draw() != 'H'
			if (!dynamic_cast<Human*>(organisms[i])) {
				output << org->Draw() << "%" << org->getPosition()[0] << "%" << org->getPosition()[1]
					<< "%" << org->getStrength() << "%" << org->getAge() << "%" << endl;
			}
			else {
				output << org->Draw() << "%" << org->getPosition()[0] << "%" << org->getPosition()[1]
				<< "%" << org->getStrength() << "%" << org->getAge() << "%"
				<< this->getHuman()->getStateOfAbility() << "%";

				if (this->getHuman()->getStateOfAbility()) {
					output << this->getHuman()->getCountRounds() << "%" <<endl;
				}
				else {
					output << this->getHuman()->getTimeout() << "%" << endl;
				}
			}
		}
		Organism* org = organisms[organisms.size()-1];
		output << org->Draw() << "%" << org->getPosition()[0] << "%" << org->getPosition()[1]
			<< "%" << org->getStrength() << "%" << org->getAge() << endl;

		output.close();
	}
}

World* World::readGameStateFromFile_2() {
	ifstream input("game_state2.txt");
	
	if (input.is_open()) {
		string line;

		getline(input, line, '%');
		sX = stoi(line);
		getline(input, line, '%');
		sY = stoi(line);
		getline(input, line, '%');
		round = stoi(line);
		
		//input organisms
		while (getline(input, line, '%')) {
			vector<int> pos = { 0, 0 };
			char sign = line[1];
			int age, strength;

			if (sign != 'H') {
				getline(input, line, '%');
				pos[0] = stoi(line);

				getline(input, line, '%');
				pos[1] = stoi(line);

				getline(input, line, '%');
				strength = stoi(line);

				getline(input, line, '%');
				age = stoi(line);

				addOrganism(sign, pos, strength, age);
			}
			else {
				int num;
				int ability;

				getline(input, line, '%');
				pos[0] = stoi(line);

				getline(input, line, '%');
				pos[1] = stoi(line);

				getline(input, line, '%');
				strength = stoi(line);

				getline(input, line, '%');
				age = stoi(line);

				getline(input, line, '%');
				ability = stoi(line);

				getline(input, line, '%');
				num = stoi(line);

				addOrganism(sign, pos, strength, age);
				if (ability == 1) {
					getHuman()->Immortality();
					getHuman()->setCountRounds(num);
				}
				else getHuman()->setTimeout(num);
			}
		} 
	}
	return this;
}


