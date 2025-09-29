#include <iostream>

#include "App.h"

int main(int ac, char* av[])
{
	try
	{
		App app;
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return (0);
}