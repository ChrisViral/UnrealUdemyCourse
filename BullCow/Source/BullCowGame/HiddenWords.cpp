#include "HiddenWords.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

TArray<FString> FHiddenWords::Words = TArray<FString>();

FString& FHiddenWords::GetRandomWord()
{
	if (Words.Num() == 0)
	{
		const FString Path = FPaths::ProjectContentDir() / TEXT("Words/WordList.txt");
		FFileHelper::LoadFileToStringArray(Words, *Path);
	}
	
	const int32 Index = FMath::RandRange(0, Words.Num() - 1);
	const FString Chosen = Words[Index];
	return Words[Index];
}
