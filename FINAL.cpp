#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PLAYERS 6
#define MAX_CARD_TYPES 7  //with green
#define MAX_CARDS_ALL 129 
#define MAX_CARDS_PER_PLAYER 65

const char* const COLORS[MAX_CARD_TYPES] = { "green", "blue", "red", "violet", "yellow", "white", "black" };

using namespace std;


struct Card
{
	int value;
	int color;
};

struct CardSet
{
	struct Card cards[MAX_CARDS_PER_PLAYER];
	int eachColorNum[MAX_CARD_TYPES];
	int numOfCards;
};

struct Player
{
	struct CardSet handCardsSet;
	struct CardSet deckCardsSet;
};

struct Pile
{
	struct CardSet pileCardsSet;
	int trackSum;
	int pileColor;
};

struct Game
{
	struct Player players[MAX_PLAYERS];
	struct Pile piles[MAX_CARD_TYPES - 1];

	FILE* inputStream;

	int numOfPlayers;
	int numOfPiles;
	int activePlayer;
	int explosionThres;
};

//chooses between console and file input
FILE* chooseInputStream() {
	const char* filename = "eg_input.txt";
	FILE* inputStream = fopen(filename, "r");

	if (inputStream == NULL) {
		cout << "Input file not found, switching to console input\n";
		inputStream = stdin;
	}

	return inputStream;
}

// 1_Deck_generation STOS
void simpleDeckGeneration() {

	int piles, greens, greenVal, numCards;
	cin >> piles >> greens >> greenVal >> numCards;

	int* deck = new int[numCards];
	for (int i = 0; i < numCards; i++) {
		cin >> deck[i];
	}

	//print values & colors
	for (int i = 0; i < piles + 1; i++) {
		if (i == 0) {
			for (int j = 0; j < greens; j++) {
				cout << greenVal << " " << COLORS[i] << " ";
			}
		}
		else {
			for (int j = 0; j < numCards; j++) {
				cout << deck[j] << " " << COLORS[i] << " ";
			}
		}
	}
	delete[] deck;
}

void addHandCardToPlayer(struct Player* player, Card card) {
	int trackIndex = player->handCardsSet.numOfCards;
	player->handCardsSet.cards[trackIndex] = card;
	player->handCardsSet.numOfCards++;
}

void addDeckCardToPlayer(struct Player* player, Card card) {
	int trackIndex = player->deckCardsSet.numOfCards;
	player->deckCardsSet.cards[trackIndex] = card;
	player->deckCardsSet.numOfCards++;
	player->deckCardsSet.eachColorNum[card.color]++;
}

void addCardToPile(struct Pile* pile, Card card) {
	int trackIndex = pile->pileCardsSet.numOfCards;
	pile->pileCardsSet.cards[trackIndex] = card;
	pile->pileCardsSet.numOfCards++;

	if (card.color != 0) {
		pile->pileColor = card.color;
	}

	pile->trackSum += card.value;
}

int readActivePlayer(FILE* inputStream) {
	char firstLine[19] = {};
	char* ret = fgets(firstLine, 19, inputStream);
	int activePlayer = firstLine[16] - '0';
	return activePlayer;
}

int readExplosionThreshold(FILE* inputStream) {
	char thirdLine[26] = {};
	char* ret = fgets(thirdLine, 26, inputStream);

	char* schowek;
	schowek = strtok(thirdLine, "=");
	schowek = strtok(NULL, " ");

	int explosionThres = atoi(schowek);
	return explosionThres;
}

int getActivePlayer(struct Game* game) {
	int newIndex = game->activePlayer + 1;
	if (newIndex > game->numOfPlayers)
		newIndex = 1;

	game->activePlayer = newIndex;
	return newIndex;
}

int readNumOfPlayers(FILE* inputStream) {
	char secondLine[20];
	char* ret = fgets(secondLine, 20, inputStream);
	int numOfPlayers = secondLine[17] - '0';
	return numOfPlayers;
}

//split line into tokens and alternately read card's color_index & value
void readPlayerCards(char line[], int indexOfPlayer, struct Game* game, bool isHand) {

	fgets(line, 1000, game->inputStream);
	char* schowek = strtok(line, ":");

	Player* currentPlayer = &game->players[indexOfPlayer];

	while (schowek != NULL) {
		int cardValue;
		schowek = strtok(NULL, " ");

		if (schowek == NULL) break;
		else cardValue = atoi(schowek);

		schowek = strtok(NULL, " ");

		if (schowek != NULL) {
			int colorIndex = 0;
			while (strstr(schowek, COLORS[colorIndex]) == NULL) {
				colorIndex++;
			}

			Card newCard = { cardValue, colorIndex };

			if (isHand) addHandCardToPlayer(currentPlayer, newCard);
			else addDeckCardToPlayer(currentPlayer, newCard);
		}
	}
	cout << "";
}

//same as readPlayerCards
void readPileCards(char line[], struct Game* game, int pileIndex) {
	fgets(line, 1000, game->inputStream);
	char* schowek;
	schowek = strtok(line, ":");

	while (schowek != NULL) {
		int cardValue;
		schowek = strtok(NULL, " ");

		if (schowek == NULL) break;
		else cardValue = atoi(schowek);

		schowek = strtok(NULL, " ");

		if (schowek != NULL) {
			int colorIndex = 0;
			while (strstr(schowek, COLORS[colorIndex]) == NULL) {
				colorIndex++;
			}

			Card newCard = { cardValue, colorIndex };
			addCardToPile(&game->piles[pileIndex], newCard);
		}
	}
	cout << "";
}

void printGameState(Game game) {

	cout << "active player = " << getActivePlayer(&game) << endl;
	cout << "players number = " << game.numOfPlayers << endl;
	cout << "explosion threshold = " << game.explosionThres << endl;

	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
		cout << playerIndex + 1 << " player hand cards: ";

		for (int cardIndex = 0; cardIndex < game.players[playerIndex].handCardsSet.numOfCards; cardIndex++) {
			Card currentCard = game.players[playerIndex].handCardsSet.cards[cardIndex];
			cout << currentCard.value << " " << COLORS[currentCard.color] << " ";
		}

		cout << endl << playerIndex + 1 << " player deck cards: ";

		for (int cardIndex = 0; cardIndex < game.players[playerIndex].deckCardsSet.numOfCards; cardIndex++) {
			Card currentCard = game.players[playerIndex].deckCardsSet.cards[cardIndex];
			cout << currentCard.value << " " << COLORS[currentCard.color] << " ";
		}

		cout << endl;
	}

	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		cout << pileIndex + 1 << " pile cards: ";

		for (int cardIndex = 0; cardIndex < game.piles[pileIndex].pileCardsSet.numOfCards; cardIndex++) {
			Card currentCard = game.piles[pileIndex].pileCardsSet.cards[cardIndex];
			cout << currentCard.value << " " << COLORS[currentCard.color] << " ";
		}

		cout << endl;
	}
}

//2_Cards_deal STOS
void dealCards(struct Game* game) {

	int piles, greens, greenVal, numCards, numOfPlayers;
	cin >> numOfPlayers >> piles >> greens >> greenVal >> numCards;

	game->numOfPlayers = numOfPlayers;
	game->activePlayer = 0;
	game->numOfPiles = piles;

	int* values = new int[numCards];
	for (int i = 0; i < numCards; i++) {
		cin >> values[i];
	}

	int counter = 0;

	for (int i = 0; i < piles + 1; i++) {
		if (i == 0) {
			for (int j = 0; j < greens; j++) {
				Player* player = &game->players[counter % numOfPlayers];
				Card card = player->handCardsSet.cards[player->handCardsSet.numOfCards];
				card.color = i;
				card.value = greenVal;
				addHandCardToPlayer(player, card);
				counter++;
			}
		}
		else {
			for (int j = 0; j < numCards; j++) {
				Player* player = &game->players[counter % numOfPlayers];
				Card card = player->handCardsSet.cards[player->handCardsSet.numOfCards];
				card.color = i;
				card.value = values[j];
				addHandCardToPlayer(player, card);
				counter++;
			}
		}
	}
	delete[] values;
}

//STOS related function
void printCountedCards(struct Game game) {

	for (int i = 0; i < game.numOfPlayers; i++) {
		cout << i + 1 << " player has " << game.players[i].handCardsSet.numOfCards << " cards on hand" << endl;
		cout << i + 1 << " player has " << game.players[i].deckCardsSet.numOfCards << " cards in front of him" << endl;
	}
	for (int i = 0; i < game.numOfPiles; i++) {
		cout << "there are " << game.piles[i].pileCardsSet.numOfCards << " cards on " << i + 1 << " pile" << endl;
	}

}

//iterates through each pile, player's deck cards and hand cards counting greens
//it checks if the first green value matches next, if not func returns
void checkGreens(struct Game game) {
	int countGreens = 0;
	int value = 0;
	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
		for (int cardIndex = 0; cardIndex < game.players[playerIndex].handCardsSet.numOfCards; cardIndex++) {
			if (countGreens == 0 && game.players[playerIndex].handCardsSet.cards[cardIndex].color == 0) {
				value = game.players[playerIndex].handCardsSet.cards[cardIndex].value;
				countGreens++;
			}
			else if (game.players[playerIndex].handCardsSet.cards[cardIndex].color == 0) {
				if (value != game.players[playerIndex].handCardsSet.cards[cardIndex].value) {
					cout << "Different green cards values occurred";
					return;
				}
				else countGreens++;
			}
		}
		for (int cardIndex = 0; cardIndex < game.players[playerIndex].deckCardsSet.numOfCards; cardIndex++) {
			if (countGreens == 0 && game.players[playerIndex].deckCardsSet.cards[cardIndex].color == 0) {
				value = game.players[playerIndex].deckCardsSet.cards[cardIndex].value;
				countGreens++;
			}
			else if (game.players[playerIndex].deckCardsSet.cards[cardIndex].color == 0) {
				if (value != game.players[playerIndex].deckCardsSet.cards[cardIndex].value) {
					cout << "Different green cards values occurred";
					return;
				}
				else countGreens++;
			}
		}
	}
	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		for (int cardIndex = 0; cardIndex < game.piles[pileIndex].pileCardsSet.numOfCards; cardIndex++) {
			if (countGreens == 0 && game.piles[pileIndex].pileCardsSet.cards[cardIndex].color == 0) {
				value = game.piles[pileIndex].pileCardsSet.cards[cardIndex].value;
				countGreens++;
			}
			else if (game.piles[pileIndex].pileCardsSet.cards[cardIndex].color == 0) {
				if (value != game.piles[pileIndex].pileCardsSet.cards[cardIndex].value) {
					cout << "Different green cards values occurred";
					return;
				}
				else countGreens++;
			}
		}
	}
	if (countGreens == 0) cout << "Green cards does not exist";
	else cout << "Found " << countGreens << " green cards, all with " << value << " value";
}

//similar to checkGreens in terms of iterating
//cardsNum array holds number of cards of each color in respective indexes
//then checks if all (except green, index 0) are the same
void checkCardsNumbers(struct Game game) {

	int cardsNum[MAX_CARD_TYPES] = {};

	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
		for (int cardIndex = 0; cardIndex < game.players[playerIndex].handCardsSet.numOfCards; cardIndex++) {
			cardsNum[game.players[playerIndex].handCardsSet.cards[cardIndex].color]++;
		}
		for (int cardIndex = 0; cardIndex < game.players[playerIndex].deckCardsSet.numOfCards; cardIndex++) {
			cardsNum[game.players[playerIndex].deckCardsSet.cards[cardIndex].color]++;
		}
	}
	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		for (int cardIndex = 0; cardIndex < game.piles[pileIndex].pileCardsSet.numOfCards; cardIndex++) {
			cardsNum[game.piles[pileIndex].pileCardsSet.cards[cardIndex].color]++;
		}
	}

	for (int i = 1; i < game.numOfPiles; i++) {
		if (cardsNum[i] != cardsNum[i + 1]) {
			cout << "At least two colors with a different number of cards were found:" << endl;
			for (int j = 1; j < game.numOfPiles + 1; j++) {
				cout << COLORS[j] << " cards are " << cardsNum[j] << endl;
			}
			return;
		}
	}
	cout << "The number cards of all colors is equal: " << cardsNum[1];
}

//function used for qsort as 'function that compares two elements'
int compare(const void* a, const void* b)
{
	int int_a = *((int*)a);
	int int_b = *((int*)b);

	if (int_a == int_b) return 0;
	else if (int_a < int_b) return -1;
	else return 1;
}

void printAllCards(int allColors[MAX_CARD_TYPES][MAX_CARDS_PER_PLAYER], struct Game game) {

	for (int i = 1; i < game.numOfPiles + 1; i++) {

		cout << COLORS[i] << " cards values: ";
		for (int j = 0; allColors[i][j] != 0; j++) {
			cout << allColors[i][j] << " ";
		}

		cout << endl;
	}
}

void compCardValues(int allColors[][MAX_CARDS_PER_PLAYER], int colorsCount[], Game game) {

	for (int i = 1; i < (MAX_CARD_TYPES - 1); i++) {
		if ((colorsCount[i] != colorsCount[i + 1]) && colorsCount[i + 1] != 0) {
			cout << "The values of cards of all colors are not identical:" << endl;
			printAllCards(allColors, game);
			return;
		}
		for (int j = 0; j < colorsCount[i]; j++) {
			if ((allColors[i][j] != allColors[i + 1][j]) && allColors[i + 1][j] != 0) {
				cout << "The values of cards of all colors are not identical:" << endl;
				printAllCards(allColors, game);
				return;
			}
		}
	}

	cout << "The values of cards of all colors are identical:" << endl;

	for (int i = 0; i < colorsCount[1]; i++) {
		cout << allColors[1][i] << " ";
	}
}

void getAllCardsAndComp(struct Game game)
{

	int allColors[MAX_CARD_TYPES][MAX_CARDS_PER_PLAYER] = {};
	int colorsCount[MAX_CARD_TYPES] = {};
	int allCount = 0;

	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
		for (int cardIndex = 0; cardIndex < game.players[playerIndex].handCardsSet.numOfCards; cardIndex++) {
			struct Card currentCard = game.players[playerIndex].handCardsSet.cards[cardIndex];
			allColors[currentCard.color][colorsCount[currentCard.color]] = currentCard.value;

			colorsCount[currentCard.color]++;
			allCount++;
		}

		for (int cardIndex = 0; cardIndex < game.players[playerIndex].deckCardsSet.numOfCards; cardIndex++) {
			struct Card currentCard = game.players[playerIndex].deckCardsSet.cards[cardIndex];
			allColors[currentCard.color][colorsCount[currentCard.color]] = currentCard.value;

			colorsCount[currentCard.color]++;
			allCount++;
		}
	}

	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		for (int cardIndex = 0; cardIndex < game.piles[pileIndex].pileCardsSet.numOfCards; cardIndex++) {
			struct Card currentCard = game.piles[pileIndex].pileCardsSet.cards[cardIndex];
			allColors[currentCard.color][colorsCount[currentCard.color]] = currentCard.value;

			colorsCount[currentCard.color]++;
			allCount++;
		}
	}

	for (int currentColor = 1; currentColor < MAX_CARD_TYPES; currentColor++) {
		qsort(allColors[currentColor], colorsCount[currentColor], sizeof(int), compare);
	}

	compCardValues(allColors, colorsCount, game);
}

int checkHands(struct Game game) {

	int* playersCardsSum = new int[game.numOfPlayers];

	for (int i = 0; i < game.numOfPlayers; i++) {
		playersCardsSum[i] = game.players[i].handCardsSet.numOfCards;
		qsort(playersCardsSum, i + 1, sizeof(int), compare);
	}

	if ((playersCardsSum[game.numOfPlayers - 1] - playersCardsSum[0]) >= 2) {
		cout << "The number of players cards on hand is wrong" << endl;
		delete[] playersCardsSum;

		return 1;
	}
	else {
		delete[] playersCardsSum;
		return 0;
	}
}

int checkPilesThreshold(struct Game game) {

	int count = 0;
	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		if (game.piles[pileIndex].trackSum > game.explosionThres) {
			cout << "Pile number " << pileIndex + 1 << " should explode earlier" << endl;
			count++;
		}
	}
	if (count == 0) return 0;
	else return 1;
}

//iterates through piles and their cards to check if there are any different color cards (excluding greens)
int checkPileColors(struct Game game) {
	int count = 0;
	int lastColor;

	for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
		Pile currentPile = game.piles[pileIndex];
		for (int cardIndex = 0; cardIndex < currentPile.pileCardsSet.numOfCards; cardIndex++) {
			Card currentCard = currentPile.pileCardsSet.cards[cardIndex];
			if ((currentPile.pileColor != currentCard.color && currentCard.color != 0) && currentPile.pileColor != 0) {
				cout << "Two different colors were found on the " << pileIndex + 1 << " pile" << endl;
				count++;
				break;
			}
		}
	}
	if (count == 0) return 0;
	else return 1;
}

void checkEverything(struct Game game) {

	int gameState = 0;

	gameState += checkHands(game);
	gameState += checkPileColors(game);
	gameState += checkPilesThreshold(game);

	if (gameState == 0) {
		cout << "Current state of the game is ok";
	}
}

//checks if any of the players has cards, if not returns true
bool checkIfRoundIsOver(Game game) {

	for (int i = 0; i < game.numOfPlayers; i++) {
		if (game.players[i].handCardsSet.numOfCards != 0) {
			return false;
		}
	}
	return true;
}

void removeFirstCardFromHand(Player* player) {
	//we have to rearrange the array and then lessen number of cards by one
	for (int i = 1; i <= player->handCardsSet.numOfCards; i++) {
		player->handCardsSet.cards[i - 1] = player->handCardsSet.cards[i];
	}
	player->handCardsSet.numOfCards--;
}

void removeCardFromHand(Player* player, Card card) {
	//seek the given card in player hand and return it's index
	int index = 0;
	for (int i = 0; i <= player->handCardsSet.numOfCards; i++) {
		Card currentCard = player->handCardsSet.cards[i];
		if (currentCard.value == card.value && currentCard.color == card.color) {
			index = i;
			break;
		}
	}

	//then rearrange array
	for (int i = index + 1; i <= player->handCardsSet.numOfCards; i++) {
		player->handCardsSet.cards[i - 1] = player->handCardsSet.cards[i];
	}
	player->handCardsSet.numOfCards--;
}

void movePileToPlayerDeck(Player* player, Pile* pile) {
	for (int pileCardIndex = 0; pileCardIndex < pile->pileCardsSet.numOfCards; pileCardIndex++) {
		addDeckCardToPlayer(player, pile->pileCardsSet.cards[pileCardIndex]);
	}
	pile->pileCardsSet = {};
	pile->pileColor = 0;
}

int whereToAdd(struct Game* game, int pilesToAdd[], struct Card lowestCard) {

	int wasMyColor = -1; //it will check if there is already pileColor of our card color
	int pileToAdd = 0;

	//first of all iterate through piles and check which ones are candidates to add card there
	//we add to the respective indexes their sum
	for (int pileIndex = 0; pileIndex < game->numOfPiles; pileIndex++) {
		Pile* currentPile = &game->piles[pileIndex];

		if (lowestCard.color == 0) {
			pilesToAdd[pileIndex] = currentPile->trackSum;
			break;
		}

		if (currentPile->pileColor == lowestCard.color) {
			pilesToAdd[pileIndex] = currentPile->trackSum;
			wasMyColor = pileIndex;
			break;
		}

		else if (currentPile->pileColor == 0) {
			pilesToAdd[pileIndex] = currentPile->trackSum;
		}
	}

	//then check their sum and colors to decide which one best fits
	for (int i = 0; i < game->numOfPiles; i++) {
		//it there is no pile of card's color and pile's sum is 0 we have to add it there
		if (wasMyColor == -1 && game->piles[i].trackSum == 0) {
			pileToAdd = i;
			return pileToAdd;
		}
		//if there was pile color of card's color and card color is not green
		else if (game->piles[i].pileColor == lowestCard.color && lowestCard.color != 0 && wasMyColor > -1) {
			pileToAdd = i;
			return pileToAdd;
		}
		else {
			//return pile which has the lowest trackSum
			if (pilesToAdd[i] < pilesToAdd[i + 1]) {
				pileToAdd = i;
			}
		}
	}
	return pileToAdd;
}

int conditionsForEasyMove(Game* game, Card firstCard) {

	//it will hold pile index
	int pileToAdd = -1;

	for (int pileIndex = 0; pileIndex < game->numOfPiles; pileIndex++) {
		Pile* currentPile = &game->piles[pileIndex];

		//check if card is green, if it is, it can go to any pile
		if (firstCard.color == 0) {
			pileToAdd = pileIndex;
			break;
		}

		//if there is already pileColor of our card color (not green) we have to add it there
		if (currentPile->pileColor == firstCard.color && firstCard.color != 0) {
			pileToAdd = pileIndex;
			break;
		}
		//if nothing changed and pileColor is null we can add any card in there
		else if (pileToAdd == -1 && currentPile->pileColor == 0) {
			pileToAdd = pileIndex;
		}
	}
	return pileToAdd;
}

void easyMove(Game* game) {

	Player* currentPlayer = &game->players[game->activePlayer - 1];
	//take first card from hand
	Card firstCard = currentPlayer->handCardsSet.cards[0];

	removeFirstCardFromHand(currentPlayer);

	//check which pile fits best
	int pileToAdd = conditionsForEasyMove(game, firstCard);

	addCardToPile(&game->piles[pileToAdd], firstCard);

	//if this card crosses the threshold add all cards to player's deck
	if (game->piles[pileToAdd].trackSum > game->explosionThres) {
		movePileToPlayerDeck(currentPlayer, &game->piles[pileToAdd]);
	}
}

void chooseHighestCard(Game* game) {

	int* pilesToAdd = new int[game->numOfPiles];

	Player* currentPlayer = &game->players[game->activePlayer - 1];
	Card highestCard = currentPlayer->handCardsSet.cards[0];

	//find highest card in hand
	for (int cardIndex = 0; cardIndex < currentPlayer->handCardsSet.numOfCards; cardIndex++) {
		if (currentPlayer->handCardsSet.cards[cardIndex].value > highestCard.value) {
			highestCard = currentPlayer->handCardsSet.cards[cardIndex];
		}
	}

	removeCardFromHand(currentPlayer, highestCard);

	int pileToAdd = whereToAdd(game, pilesToAdd, highestCard);

	addCardToPile(&game->piles[pileToAdd], highestCard);

	if (game->piles[pileToAdd].trackSum > game->explosionThres) {
		movePileToPlayerDeck(currentPlayer, &game->piles[pileToAdd]);
	}

	delete[] pilesToAdd;
}

void chooseOptimalCard(Game* game) {

	int pileToAddIndex = 0;
	Card cardToAdd = {};

	Player* currentPlayer = &game->players[game->activePlayer - 1];

	//iterate through deck cards & piles and check if current card meets pile's cryteria
	for (int cardIndex = 0; cardIndex < currentPlayer->handCardsSet.numOfCards; cardIndex++) {
		Card currentCard = currentPlayer->handCardsSet.cards[cardIndex];
		for (int pileIndex = 1; pileIndex <= game->numOfPiles; pileIndex++) {
			Pile currentPile = game->piles[pileIndex - 1];
			if (currentPile.pileColor == 0 || currentPile.pileColor == currentCard.color || currentCard.color == 0) {
				//if meets cryteria check which card is closest to reaching explosion threshold 
				if (currentPile.trackSum + currentCard.value <= game->explosionThres) {
					int eq1 = game->explosionThres - (currentPile.trackSum + cardToAdd.value);
					int eq2 = game->explosionThres - (currentPile.trackSum + currentCard.value);
					if (eq1 > eq2) {
						cardToAdd = currentCard;
						pileToAddIndex = pileIndex;
					}
				}
			}
		}
	}
	if (pileToAddIndex != 0) {
		addCardToPile(&game->piles[pileToAddIndex - 1], cardToAdd);
		removeCardFromHand(currentPlayer, cardToAdd);
		return;
	}
	//if none of the cards meet cryteria choose highest card
	chooseHighestCard(game);
}

void chooseLowestCard(Game* game) {

	int* pilesToAdd = new int[game->numOfPiles];

	Player* currentPlayer = &game->players[game->activePlayer - 1];
	Card lowestCard = currentPlayer->handCardsSet.cards[0];

	//find lowest card
	for (int cardIndex = 0; cardIndex < currentPlayer->handCardsSet.numOfCards; cardIndex++) {
		if (currentPlayer->handCardsSet.cards[cardIndex].value < lowestCard.value) {
			lowestCard = currentPlayer->handCardsSet.cards[cardIndex];
		}
	}

	int pileToAdd = whereToAdd(game, pilesToAdd, lowestCard);

	//if lowest card leads to explosion, choose highest card
	if (game->piles[pileToAdd].trackSum + lowestCard.value > game->explosionThres) {
		chooseHighestCard(game);
	}
	else {
		addCardToPile(&game->piles[pileToAdd], lowestCard);
		removeCardFromHand(currentPlayer, lowestCard);
	}
	delete[] pilesToAdd;
}

void saveGameStateToFile(Game game) {

	int activePlayer = getActivePlayer(&game);

	FILE* file;
	file = fopen("eg_input.txt", "w");

	if (file == NULL)
	{
		printf("File failed to open.");
	}
	else {
		fprintf(file, "active player = %d\n", activePlayer);
		fprintf(file, "players number = %d\n", game.numOfPlayers);
		fprintf(file, "explosion threshold = %d\n", game.explosionThres);

		for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {

			fprintf(file, "%d player hand cards:", playerIndex + 1);
			for (int cardIndex = 0; cardIndex < game.players[playerIndex].handCardsSet.numOfCards; cardIndex++) {
				Card currentCard = game.players[playerIndex].handCardsSet.cards[cardIndex];
				fprintf(file, " %d %s", currentCard.value, COLORS[currentCard.color]);
			}

			fprintf(file, "\n");
			fprintf(file, "%d player deck cards:", playerIndex + 1);

			for (int cardIndex = 0; cardIndex < game.players[playerIndex].deckCardsSet.numOfCards; cardIndex++) {
				Card currentCard = game.players[playerIndex].deckCardsSet.cards[cardIndex];
				fprintf(file, " %d %s", currentCard.value, COLORS[currentCard.color]);
			}

			fprintf(file, "\n");
		}
		for (int pileIndex = 0; pileIndex < game.numOfPiles; pileIndex++) {
			fprintf(file, "%d pile cards:", pileIndex + 1);

			for (int cardIndex = 0; cardIndex < game.piles[pileIndex].pileCardsSet.numOfCards; cardIndex++) {
				Card currentCard = game.piles[pileIndex].pileCardsSet.cards[cardIndex];
				fprintf(file, " %d %s", currentCard.value, COLORS[currentCard.color]);
			}
			fprintf(file, "\n");
		}
	}
	fclose(file);
}

int calculateNumberOfPiles(Game game) {

	int highestColor = 0;
	//uses the fact that the highest color index is at the same time number of piles
	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {

		CardSet handCards = game.players[playerIndex].handCardsSet;
		for (int cardIndex = 0; cardIndex < handCards.numOfCards; cardIndex++) {
			if (highestColor < handCards.cards[cardIndex].color) {
				highestColor = handCards.cards[cardIndex].color;
			}
		}

		CardSet deckCards = game.players[playerIndex].deckCardsSet;
		for (int cardIndex = 0; cardIndex < deckCards.numOfCards; cardIndex++) {
			if (highestColor < deckCards.cards[cardIndex].color) {
				highestColor = deckCards.cards[cardIndex].color;
			}
		}
	}
	return highestColor;
}

void scores(int whoIsResistant[], Game game) {

	int scores[MAX_PLAYERS] = {};

	for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
		CardSet currentPlayerDeckCards = game.players[playerIndex].deckCardsSet;
		for (int cardIndex = 0; cardIndex < currentPlayerDeckCards.numOfCards; cardIndex++) {
			Card currentCard = currentPlayerDeckCards.cards[cardIndex];

			if (currentCard.color == 0) {
				scores[playerIndex] += 2;
			}
			else if (whoIsResistant[currentCard.color] == playerIndex + 1) {
				scores[playerIndex] += 0;
			}
			else {
				scores[playerIndex] += 1;
			}
		}
	}
	for (int i = 0; i < game.numOfPlayers; i++) {
		cout << "Wynik gracza " << i + 1 << " = " << scores[i] << endl;
	}
}

void printEndGame(Game game) {

	int whoIsResistant[MAX_CARD_TYPES] = {};

	for (int colorIndex = 1; colorIndex <= game.numOfPiles; colorIndex++) {
		int trackIndex = 0;
		for (int playerIndex = 0; playerIndex < game.numOfPlayers; playerIndex++) {
			CardSet currentPlayerDeckCards = game.players[playerIndex].deckCardsSet;
			CardSet trackIndexPlayerDeckCards = game.players[trackIndex].deckCardsSet;
			if (currentPlayerDeckCards.eachColorNum[colorIndex] > trackIndexPlayerDeckCards.eachColorNum[colorIndex]) {
				trackIndex = playerIndex;
				whoIsResistant[colorIndex] = trackIndex + 1;
			}
			else if (currentPlayerDeckCards.eachColorNum[colorIndex] == trackIndexPlayerDeckCards.eachColorNum[colorIndex]) {
				if (playerIndex == 0) {
					trackIndex = playerIndex;
					whoIsResistant[colorIndex] = trackIndex + 1;
				}
				else whoIsResistant[colorIndex] = 0;
			}
		}
	}

	for (int colorIndex = 1; colorIndex <= game.numOfPiles; colorIndex++) {
		if (whoIsResistant[colorIndex] != 0) {
			cout << "Na kolor " << COLORS[colorIndex] << " odporny jest gracz " << whoIsResistant[colorIndex] << endl;
		}
	}

	scores(whoIsResistant, game);
}

void initGameStateFromInput(Game* game, char line[]) {

	game->activePlayer = readActivePlayer(game->inputStream);
	game->numOfPlayers = readNumOfPlayers(game->inputStream);
	game->explosionThres = readExplosionThreshold(game->inputStream);

	for (int j = 0; j < game->numOfPlayers; j++)
	{
		readPlayerCards(line, j, game, true);
		readPlayerCards(line, j, game, false);
	}

	game->numOfPiles = calculateNumberOfPiles(*game);

	for (int i = 0; i < game->numOfPiles; i++)
	{
		readPileCards(line, game, i);
	}
}

int main() {

	//struct Game game = {};
	char line[1000];
	
	//while(true) {

		struct Game game = {};

		game.inputStream = chooseInputStream();

		initGameStateFromInput(&game, line);

		chooseHighestCard(&game);

		saveGameStateToFile(game);

		//saveGameStateToFile2(game);
		
	//	if(checkIfRoundIsOver(game)) {
	//		printEndGame(game);
	//		return 0;
	//	} 
	//}

	return 0;
}