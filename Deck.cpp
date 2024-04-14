#include "Deck.h"
#include <algorithm>
#include <random>
#include "Controller.h"

Deck::deck Deck::activeDeck;
std::vector<Deck::player> Deck::players;
int Deck::playersTurn = 0;

Deck::deck Deck::loadDeck(int set)
{
	Artist artist;
	deck tempDeck;

	tempDeck.master.push_back({ 0, artist.loadTexture("Resource/cards/0.png") });
	tempDeck.master.push_back({ 0, artist.loadTexture("Resource/cards/0.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 1, artist.loadTexture("Resource/cards/1.png") });
	tempDeck.master.push_back({ 2, artist.loadTexture("Resource/cards/2.png") });
	tempDeck.master.push_back({ 2, artist.loadTexture("Resource/cards/2.png") });
	tempDeck.master.push_back({ 3, artist.loadTexture("Resource/cards/3.png") });
	tempDeck.master.push_back({ 3, artist.loadTexture("Resource/cards/3.png") });
	tempDeck.master.push_back({ 4, artist.loadTexture("Resource/cards/4.png") });
	tempDeck.master.push_back({ 4, artist.loadTexture("Resource/cards/4.png") });
	tempDeck.master.push_back({ 5, artist.loadTexture("Resource/cards/5.png") });
	tempDeck.master.push_back({ 5, artist.loadTexture("Resource/cards/5.png") });
	tempDeck.master.push_back({ 6, artist.loadTexture("Resource/cards/6.png") });
	tempDeck.master.push_back({ 6, artist.loadTexture("Resource/cards/6.png") });
	tempDeck.master.push_back({ 7, artist.loadTexture("Resource/cards/7.png") });
	tempDeck.master.push_back({ 8, artist.loadTexture("Resource/cards/8.png") });
	tempDeck.master.push_back({ 9, artist.loadTexture("Resource/cards/9.png") });

	tempDeck.back = artist.loadTexture("Resource/cards/back.png");

	return tempDeck;
}

void Deck::shuffle(deck* shuffleDeck)
{
	shuffleDeck->activeStack = shuffleDeck->master;

	//shuffle
	auto rng = std::default_random_engine{Uint32(rand())};
	std::shuffle(shuffleDeck->activeStack.begin(), shuffleDeck->activeStack.end(), rng);

	shuffleDeck->out = shuffleDeck->activeStack.back();
	shuffleDeck->activeStack.pop_back();
}

void deal(Deck::deck* deadDeck)
{
	for (int i = 0; i < Deck::players.size(); i++)
	{
		Deck::players[i].hand.push_back(Deck::activeDeck.activeStack.back());
		Deck::activeDeck.activeStack.pop_back();
	}
}

void grab(Deck::deck* grabDeck, Deck::player* grabPlayer)
{
	grabPlayer->hand.push_back(Deck::activeDeck.activeStack.back());
	Deck::activeDeck.activeStack.pop_back();
}

void play(int playerID, int cardID)
{
	//make it run play func attached to card
	Deck::players[playerID].discard.push_back(Deck::players[playerID].hand[cardID]);
	Deck::players[playerID].hand.erase(Deck::players[playerID].hand.begin() + cardID);
}

bool isOverCard(SDL_Point point, int playerID, int cardID)
{
	//see if point is within the card box, need to do some jank math to find out card box using players ID and card number
	//something like playerID * 256 + cardID * 64

	return true;
}

void drawDeck(Deck::deck* drawDeck)
{
	Artist artist;
	// 
	//debug for drawing contents of deck
	//for (int i = 0; i < drawDeck->activeStack.size(); i++)
	//{
	//	artist.drawImage(Deck::activeDeck.activeStack[i].tex, i%10*64, i/10*64);
	//}
	//
	//artist.drawImage(Deck::activeDeck.out.tex, 10 * 64 + 160, 0);
	artist.drawImage(Deck::activeDeck.back, 32, 0, 0, 0, 90);
	for (int i = 0; i < Deck::activeDeck.activeStack.size(); i++)
	{
		artist.drawImage(Deck::activeDeck.back, 32 + i * 3, 0);
	}
	if (Deck::activeDeck.activeStack.size() > 0)
		artist.drawLetters(std::to_string(Deck::activeDeck.activeStack.size()), 32, 224 - 26, Artist::smallFont);
}

void drawHands(std::vector<Deck::player> players)//make pointer?
{
	Artist artist; //FIX

	

	for (int i = 0; i < players.size(); i++)
	{
		//draw name
		artist.drawLetters(players[i].name, i * 256, Artist::SCREEN_HEIGHT - 224 - 32, Artist::smallFont);
		//draw hands
		if (i == Deck::playersTurn)
		{
			for (int j = 0; j < players[i].hand.size(); j++)
			{
				artist.drawImage(players[i].hand[j].tex, i * 256 + j * 64, Artist::SCREEN_HEIGHT - 224);
			}
		}
		else
		{
			for (int j = 0; j < players[i].hand.size(); j++)
			{
				artist.drawImage(Deck::activeDeck.back, i * 256 + j * 64, Artist::SCREEN_HEIGHT - 224);
			}
		}
		//draw discard pile
		for (int j = 0; j < players[i].discard.size(); j++)
		{
			artist.drawImage(players[i].discard[j].tex, i * 256 + j * 64, Artist::SCREEN_HEIGHT - 224* 2 - 30);
		}
	}
}




void Deck::draw()
{
	drawDeck(&Deck::activeDeck);
	drawHands(Deck::players);
}

void Deck::controller()
{
	//reset and shuffle
	if (Controller::keyboardStates[SDL_SCANCODE_SPACE] == 1)
	{
		//reset players
		players.clear();
		playersTurn = 0;

		shuffle(&activeDeck);
	}
	//select player count and deal hands
	if (Controller::keyboardStates[SDL_SCANCODE_2] == 1)//needs more logic for puting 3 out face up
	{
		players.push_back({ "Player1" });
		players.push_back({ "Player2" });
	}
	if (Controller::keyboardStates[SDL_SCANCODE_3] == 1)
	{
		players.push_back({ "Player1" });
		players.push_back({ "Player2" });
		players.push_back({ "Player3" });
	}
	if (Controller::keyboardStates[SDL_SCANCODE_4] == 1)
	{
		players.push_back({ "Player1" });
		players.push_back({ "Player2" });
		players.push_back({ "Player3" });
		players.push_back({ "Player4" });
	}
	if (Controller::keyboardStates[SDL_SCANCODE_5] == 1)
	{
		players.push_back({ "Player1" });
		players.push_back({ "Player2" });
		players.push_back({ "Player3" });
		players.push_back({ "Player4" });
		players.push_back({ "Player5" });
	}
	//deal cards for first hands
	if (Controller::keyboardStates[SDL_SCANCODE_S] == 1)
	{
		deal(&Deck::activeDeck);
	}
	//change whos turn it is manualy
	if (Controller::keyboardStates[SDL_SCANCODE_RIGHT] == 1)
	{
		playersTurn++;
		if (playersTurn >= players.size())
		{
			playersTurn = 0;
		}
	}
	if (Controller::keyboardStates[SDL_SCANCODE_LEFT] == 1)
	{
		playersTurn--;
		if (playersTurn < 0)
		{
			playersTurn = players.size()-1;
		}
	}
	//draw card to current player
	if (Controller::keyboardStates[SDL_SCANCODE_D] == 1)
	{
		grab(&Deck::activeDeck, &players[playersTurn]);
	}
	//play a card
	if (Controller::keyboardStates[SDL_SCANCODE_P] == 1)
	{
		play(playersTurn, 0);
	}
}