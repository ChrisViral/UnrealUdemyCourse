// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int8 Lives;

	bool IsGameOver() const
	{
		return Lives == 0;
	}

	bool IsGuessValid(const FString& Guess) const;
	FBullCowCount GetBullsAndCows(const FString& Guess) const;
	static bool IsIsogram(const FString& Word);
};
