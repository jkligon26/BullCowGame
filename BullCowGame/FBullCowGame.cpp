#include "FBullCowGame.h"
#include <iostream>
#include <map>
#pragma once
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { reSet(); }

void FBullCowGame::reSet()
{
	const FString HIDDEN_WORD = "astronomy"; //MUST be an isogram
	currentTry = 1;
	hiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
} //default constructor


int32 FBullCowGame::getCurrentTry() const { return currentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return hiddenWord.length(); }

bool FBullCowGame::isGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::isValidGuess(FString userGuess) const 
{ 
	if (!isIsogram(userGuess)) //if guess isn't an isogram, return an error 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(userGuess)) //if guess isn't all lower case, return an error TODO write function 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (userGuess.length() != getHiddenWordLength()) //if the guess length is wrong
	{
			return EGuessStatus::Wrong_Length;
	}
	else return EGuessStatus::OK;

}


int32 FBullCowGame::getMaxTries() const 
{ 
	TMap<int32, int32> wordLengthMaxTries{ {3, 4}, {4,5}, {5,5}, {6,8}, {7,8}, {8,9}, {9,9} };

	return wordLengthMaxTries[hiddenWord.length()]; 
	//the input lenght corresponds to the first int32
	//it would then equate to the secondt int32 and put that in as max tries
}


FBullCowCount FBullCowGame::submitValidGuess(FString userGuess)
{
	//receives a valid guess and increments and returns count.
	currentTry++; 
	FBullCowCount bullCowCount; 	
	int32 wordLength = 0;
	wordLength = hiddenWord.length(); //assuming same length as guess



	//loop through all letters in the hidden word
	for (int32 i = 0; i < wordLength; ++i)
	{
		//compare letters against the guess
		for (int32 j = 0; j < wordLength; ++j)
		{
			//if match then
			if (userGuess[j] == hiddenWord[i])
			{
				//if same place
				if (i == j)
				{
					//increment bulls
					bullCowCount.Bulls++;
				}
				else
				{
					//increment cows
					bullCowCount.Cows++;
				}
			}
		}
	}

	if (bullCowCount.Bulls == wordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString userGuess) const
{ 
	//treat 0 and 1 letter words as isogram
	if (userGuess.length() <= 1) { return true; }

	//using TMap
	TMap<char, bool> letterSeen;
	for (auto letter : userGuess) //':' = 'in', for all letters of the word
	{
		letter = tolower(letter); //handle mixed case
		if (letterSeen[letter]) { return false; } //no isograme
		else { letterSeen[letter] = true; } //add letter to the map as seen
	}
	/*std::map syntax == std::map<char,bool> name
	to access:
	name[letter]*/

	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString userGuess) const
{
	for (auto letter : userGuess)
	{
		if (!islower(letter)) { return false; } //if a letter is NOT lower, return false
	}
	
	return true;
}
