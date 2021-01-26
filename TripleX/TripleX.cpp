#include <iostream>
#include <random>

constexpr int START_DIFFICULTY = 2;
constexpr int MAX_DIFFICULTY = 10;

int inline RandomDifficulty(const int Difficulty)
{
	return rand() % Difficulty + Difficulty;
}

bool PlayGame(const int Difficulty)
{
	//Intro message for level
	std::cout << "You are faced with a code lock of level " << Difficulty << std::endl;
	
	//Numbers setup
	const int CodeA = RandomDifficulty(Difficulty);
	const int CodeB = RandomDifficulty(Difficulty);
	const int CodeC = RandomDifficulty(Difficulty);
	const int CodeSum = CodeA + CodeB + CodeC;
	const int CodeProduct = CodeA * CodeB * CodeC;

	//Show code target
	std::cout << "The code is made up of three numbers" << std::endl;
	std::cout << "Code sum: " << CodeSum << std::endl;
	std::cout << "code product: " << CodeProduct << std::endl << std::endl;

	//Get guesses
	int GuessA, GuessB, GuessC;
	std::cout << "Enter your guesses: ";
	std::cin >> GuessA >> GuessB >> GuessC;
	const int GuessSum = GuessA + GuessB + GuessC;
	const int GuessProduct = GuessA * GuessB * GuessC;

	//Print game result
	const bool bWon = GuessSum == CodeSum && GuessProduct == CodeProduct;
	std::cout << std::endl << (bWon ? "~~~ The door unlocks!! ~~~\n" : "XXX The lock remains shut  and the code resets. XXX\n") << std::endl;

	return bWon;
	
}

int main()  //NOLINT(bugprone-exception-escape)
{
	//Intro prompt
	std::cout <<  "/~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\\" << std::endl;
	std::cout <<  " * You are a secret agent breaking into a secure server room * " << std::endl;
	std::cout <<  " *        Enter the correct door codes to progress...        * " << std::endl;
	std::cout << "\\~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~/\n" << std::endl;

	//Seed RNG
	srand(std::random_device()());

	//Game loop
	for (int Difficulty = START_DIFFICULTY; Difficulty <= MAX_DIFFICULTY; /*Difficulty++*/)
	{
		//Increment difficulty when correct
		if (PlayGame(Difficulty))
		{
			Difficulty++;
		}

		//Clear input errors
		std::cin.clear();
		std::cin.ignore();
	}

	std::cout << "========== Congratulations, you have reached the server! ==========" << std::endl;
	
    return EXIT_SUCCESS;
}
