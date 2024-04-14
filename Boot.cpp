#include <stdio.h>
#include "Artist.h"
#include "Controller.h"
//TEMP
#include "Deck.h"
#include <time.h>



int main(int argc, char* args[])
{
	//Declare Artist and controller
	Artist Artist;
	Controller controller;
	

	//Start up SDL and create window
	if (!Artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!Artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}

		//set random seed
		srand(time(NULL));

		//loading setting ect
		controller.loadController();
		//TEMP
		Deck::activeDeck = Deck::loadDeck(0);
		Deck::shuffle(&Deck::activeDeck);


		//While application is running
		while (!Controller::quit)
		{
			//Clear screen
			Artist.clearScreen();


			//Checks for user input
			controller.controller();

			

			//Draw everything
			Artist.draw();






			//Update screen
			Artist.updateScreen();
		}

	}

	//Free resources and close SDL
	Artist.close();

	return 0;
}