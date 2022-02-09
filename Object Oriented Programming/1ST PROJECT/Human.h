#pragma once
#include "Animal.h"

class Human : public Animal {
	int countRounds;
	int timeout;
	bool isImmortal;

public:
	Human();
	~Human();
	Human(World* world, vector<int> pos);
	Human(World* world, vector<int> pos,
		int strength, int age);

	void Action() override;
	void Collision(Organism* collider) override;

	void Immortality();
	Human* Reproduce(vector<int> pos) override;
	bool getStateOfAbility();
	int getCountRounds();
	int getTimeout();
	bool checkIfImmortal();
	void setTimeout(int t);
	void setCountRounds(int c);
};