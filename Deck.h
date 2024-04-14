#pragma once
#include <vector>
#ifndef Artist
#include "Artist.h"
#endif
/*
2 0
6 1
2 2
2 3
2 4
2 5
2 6
1 7
1 8
1 9
*/
class Deck {
public:
	struct card {
		int power;
		SDL_Texture* tex;
		//func pointer for played effect
	};
	struct deck {
		std::vector<card> master;
		std::vector<card> activeStack;
		card out;
		SDL_Texture* back;
	};
	struct player {
		std::string name;
		std::vector<card> hand;
		std::vector<card> discard;
		bool handmaiden = 0; //clear at start of turn
	};

	static deck activeDeck;
	static std::vector<player> players;
	static int playersTurn;

	static deck loadDeck(int set);
	static void shuffle(deck* shuffleDeck);
	static void draw();
	static void controller();
};