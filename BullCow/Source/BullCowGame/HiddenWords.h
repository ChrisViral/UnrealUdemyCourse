#pragma once
#include "CoreMinimal.h"

class FHiddenWords final
{
	public:
	static FString& GetRandomWord();

	private:
	static TArray<FString> Words;

	//Prevents creating instances
	FHiddenWords() { }
};