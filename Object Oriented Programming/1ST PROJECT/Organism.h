#pragma once
#include <vector>
#include "World.h"
using namespace std;

//forward declaration
class World;

class Organism {
	int strength, initiative;
	char sign;
	vector<int> position;
	int age;
	World* world;

	friend bool operator == 
		(const Organism& org1, const Organism& org2);

public:

	Organism();
	~Organism();

	virtual void Action();
	virtual void Collision(Organism* collided);
	virtual Organism* Reproduce(vector<int> pos) = 0;
	virtual void addFeed(Organism* w, Organism* l);

	vector<int> newPosition(vector<int> pos); //find empty field
	bool checkIfSurrounded(vector<int> pos);
	Organism* checkField(vector<int> pos);
	bool checkPosition(vector<int> pos);
	char Draw();

	//GETTERS
	int getAge() const;
	int getInitiative() const;
	int getStrength() const;
	World* getWorld() const;
	vector<int> getPosition() const;

	//SETTERS
	void setAge(int a);
	void setStrength(int str);
	void setInitiative(int init);
	void setSign(char sign);
	void setPosition(vector<int> pos);
	void setWorld(World* world);

};