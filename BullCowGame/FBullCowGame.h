/*The game logic with no view code or user interaction
Game is a simple guess the world game based on Mastermind*/

#pragma once
#include <string>

//To make syntax Unreal friend
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus //strong enum
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
class FBullCowGame
{
public:
	
	FBullCowGame(); //Constructor
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus isValidGuess(FString) const;

	void reSet();
	//New Type submitValidGuess(FString)
	
	//Count bulls and cows and increase try #, assuming valid guess
	FBullCowCount submitValidGuess(FString); 

private:
	int32 currentTry;
	FString hiddenWord;
	bool bGameIsWon;

	bool isIsogram(FString) const;
	bool isLowercase(FString) const;

};