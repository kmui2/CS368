////////////////////////////////////////////////////////////////////////////////
// File Name:      a1.cpp
//
// Author:         Kevin Mui
// CS email:       mui@cs.wisc.edu
//
// Description:    A program that outputs information about myself
//                 and repeats a string.
//
// Sources:        Assignment Instructions
//
// URL(s) of sources:
//                 None>
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int main() {
	std::cout << "-+-+-+-+-+-+-+-+-+-+-+-+-\n";
	std::cout << "Name: Kevin Mui\n";
	std::cout << "Major Computer Engineering\n";
	std::cout << "Year: Junior\n";
	std::cout << "Reason I am taking this class: C++ is great for server performance.\n";
	std::cout << "-+-+-+-+-+-+-+-+-+-+-+-+-\n";
	std::cout << "\n";
	std::cout << "Number of times to loop: ";
	
	int loops;
	std::cin >> loops;

	int i;
	for (i = 0; i < loops; i++)
		std::cout << "-=-";
	std::cout << "\n";

	return 0;
}
