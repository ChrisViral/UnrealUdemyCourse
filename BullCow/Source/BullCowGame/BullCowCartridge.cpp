// Fill out your copyright notice in the Description page of Project Settings.

#include "BullCowCartridge.h"
#include "HiddenWords.h"
#include "Containers/Set.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	
	HiddenWord = *FHiddenWords::GetRandomWord();
	Lives = HiddenWord.Len();
	
	//PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); //DEBUG
	PrintLine(TEXT("Welcome to Bull Cows!\nGuess the %i letter code word:"), HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (IsGameOver())
	{
		if (Input == "yes")
		{
			ClearScreen();
			BeginPlay();
		}
		else
		{
			//Quit game
		}
	}
	else if (IsGuessValid(Input.ToLower()))
	{
		PrintLine(TEXT("Congratulations, you win!\nPlay again?"));
	}
	else
	{
		Lives--;
		if (IsGameOver())
		{
			PrintLine(TEXT("TNo more lives, you lose...\nThe word was %s\nPlay again?"), *HiddenWord);
		}
		else
		{
			const FBullCowCount Count = GetBullsAndCows(Input);
			PrintLine(TEXT("Your guess has %i bulls and %i cows.\nYou have %i lives remaining."), Count.Bulls, Count.Cows, Lives);
		}
	}
}

bool UBullCowCartridge::IsGuessValid(const FString& Guess) const
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("Correct! The word was %s"), *HiddenWord);
		return true;
	}
	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("Incorrect length, the code word has %i letters."), HiddenWord.Len());
		return false;
	}
	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("The word is not an Isogram."));
		return false;
	}
	
	PrintLine(TEXT("The word is incorrect."));
	return false;
}

FBullCowCount UBullCowCartridge::GetBullsAndCows(const FString& Guess) const
{
	FBullCowCount Count;

	static TSet<TCHAR> Seen = TSet<TCHAR>();
	for (int32 i = 0; i < Guess.Len(); i++)
	{
		const TCHAR GuessChar = Guess[i];
		const TCHAR HiddenChar = HiddenWord[i];
		//Bulls are two characters placed at the same position
		if (GuessChar == HiddenChar)
		{
			Count.Bulls++;
		}
		else
		{
			//Cows are two characters present somewhere else in the string
			if (Seen.Contains(HiddenChar))
			{
				Count.Cows++;
			}
			if (Seen.Contains(GuessChar))
			{
				Count.Cows++;
			}

			//Keep track of the characters we've seen so far
			Seen.Add(GuessChar);
			Seen.Add(HiddenChar);
		}
	}
	Seen.Empty();

	return Count;
}


bool UBullCowCartridge::IsIsogram(const FString& Word)
{
	return TSet<TCHAR>(Word.GetCharArray()).Num() == Word.Len();
}
