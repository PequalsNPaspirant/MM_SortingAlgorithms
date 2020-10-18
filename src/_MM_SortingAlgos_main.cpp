// Test.cpp : Defines the entry point for the console application.

#include <iostream>

#include "Timer/Timer_Timer.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	//Global function declarations
	//void Sorting();
	MM_DEFINE_FLAG(true, sortingUnitTests);
}

using namespace mm;

int main(int argc, char* argv[])
{
	//Sorting();
	MM_RUN_UNIT_TESTS

	cout << "\n\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " CONGRATULATIONS!!! End of program reached successfully.\n\n\n";

	std::cin.get();
	return 0;
}

