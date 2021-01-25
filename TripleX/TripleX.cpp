#include <iostream>

int main()
{
	try
	{
		std::cout << "You are a secret agent breaking into a secure server room" << std::endl;
		std::cout << "Enter the secret code to continue..." << std::endl;
	}
	catch (...)
	{
		return 1;
	}
    return 0;
}
