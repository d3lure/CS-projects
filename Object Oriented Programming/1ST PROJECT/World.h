#pragma once
#include "Organism.h"
#include <vector>
#include <string>
using namespace std;

//forward declaration
class Organism;
class Human;

class World {
	int sX, sY, round;
	vector<Organism*> organisms;
	string feed;
	char humanDirection;
	Human* human;
	void sortOrganisms();

public:
	World(int sX, int sY);
	World(int sX, int sY, int n);
	World();
	~World();

	//SETTERS
	void setX(int x);
	void setY(int y);
	void setDirection(char d);
	void setHuman(Human* h);

	//GETTERS
	int getX() const;
	int getY() const;
	int getRound() const;
	char getDirection() const;
	vector<Organism*> getOrganisms() const;
	Organism* getOrganism(int index) const;
	Human* getHuman();

	int numOfOrganisms();
	void makeRound();
	void printWorld();
	void addOrganism(Organism* org);
	void killOrganism(Organism* org);
	void gameFeed(string log);
	string getStateOfAbility();
	void saveToFile_1();
	void saveToFile_2();
	World* readGameStateFromFile_1();
	World* readGameStateFromFile_2();
	void escAnimation();
	void addOrganism(char sign, vector<int>);
	void addOrganism(char sign, vector<int>, 
		int strength, int age);
};