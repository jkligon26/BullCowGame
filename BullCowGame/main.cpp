/*This is the console executable, that makes use of the BullCow class
Acts as the view in MVC pattern, and is reponsible for all
user int32eraction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream> //pre-processor directive
#include <string>
#include "FBullCowGame.h"

//To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void Printintro();
void PlayGame();
FText getValidGuess();
bool PlayAgain();
void printGameSummary();

FBullCowGame BCGame; //Instantiate a new game


int main()
{
	bool bPlayAgain = false;
	do
	{
		Printintro();
		PlayGame();
		bPlayAgain = PlayAgain();
	} while (bPlayAgain);



	return 0;
}

void PlayGame()
{
	//Plays a single game to completion
	BCGame.reSet();
	int32 maxTries = BCGame.getMaxTries();

	//loop asking for guesses while the name is NOT won
	//and there are still turns

	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries)
	{
		FText Guess = getValidGuess(); 
	

		//Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.submitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	printGameSummary();

	return;
	
}

//Loop continually until the user gives valid guess
FText getValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//Get a guess from the player
		int32 currentTry = BCGame.getCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.getMaxTries();
		std::cout << ". Enter your guess: ";
	
		std::getline(std::cin, Guess); //Allows to take in two words

		Status = BCGame.isValidGuess(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter guess in lower case." << std::endl << std::endl;
			break;
		default: //assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //Keep looping until we get valid input
	return Guess;

}

void Printintro ()
{ 
	std::cout << "Welcome to Bulls and Cow Game, a fun word game" << std::endl;
	std::cout << "Can you guess the ";
	std::cout << BCGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}

bool PlayAgain()
{
	std::cout << std::endl;
	std::cout << "Do you want to play again? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		return true;
	}
	else return false;
}

void printGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "You won!" << std::endl;
	}
	else
		std::cout << "Bad luck. You lose." << std::endl;

	return;
}
