#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "World.h"
#include "Human.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ABILITY 32   //SPACE
#define ESC 27       //ESC

int main() {
	SetConsoleTitle(TEXT("Maciej Matuszewski 184480"));
	srand(time(NULL));
	World* world = new World();

	//START_MENU
	int opt;
	std::cout << "Generate random world, press 1" << endl;
	std::cout << "Initialize world from file, press 2" << endl;
	std::cin >> opt;

	if (opt == 1) {
		system("CLS");
		int sX, sY, n;
		std::cout << "Enter dimensions of the world" << endl;
		std::cout << "X value: ";
		std::cin >> sX;
		std::cout << "Y value: ";
		std::cin >> sY;
		std::cout << "Number of organisms: ";
		std::cin >> n;
		world = new World(sX, sY, n);
		
	}
	else if (opt == 2) {
		system("CLS");
		int op;
		std::cout << "From 'game_state', press 1" << endl;
		std::cout << "From 'game_state2', press 2" << endl;
		std::cin >> op;
		if (op == 1) world->readGameStateFromFile_1();
		else if (op == 2) world->readGameStateFromFile_2();
		
	}
	//----------------------------------------------------//

	system("CLS");
	world->printWorld();
	int key;

	//MAIN LOOP
    while(true) {
		key = _getch();
		if (key == 224) key = _getch();
		switch (key) {
			case KEY_UP:
				world->setDirection('u');
				break;

			case KEY_RIGHT:
				world->setDirection('r');
				break;

			case KEY_DOWN:
				world->setDirection('d');
				break;

			case KEY_LEFT:
				world->setDirection('l');
				break;

			case ABILITY:
				world->setDirection(NULL);
				world->getHuman()->Immortality();
				break;

			case ESC: {
				world->saveToFile_1();
				world->saveToFile_2();
				world->escAnimation();
				return 0;
			}
		}
		system("CLS");
		world->makeRound();
    }
	return 0;
}
