////////////////////////////////////////////////////////////////////////////////
// File Name:      a1.cpp
//
// Author:         <Your Name>
// CS email:       <Your CS email>
//
// Description:    A program that outputs information about myself
//                 and repeats a string.
//
// Sources:        <Your sources, if any>
//
// URL(s) of sources:
//                 <URLs of your sources, if any>
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
	std::cin << loops;
	std::cout << "\n";

	int i;
	for (i = 0; i < loops; i++)
		std::cout << "-=-";

	return 0;
}
