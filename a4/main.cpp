///////////////////////////////////////////////////////////////////////////////
// File Name:      main.cpp
//
// Author:         Gerald, Isaac, Varun
// CS email:       gerald@cs.wisc.edu, isung@cs.wisc.edu, vnaik@cs.wisc.edu
//
// Description:    The main program for a4.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#include "GradStudent.hpp"
#include "processStudent.hpp"
#include "UndergradStudent.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

/**
 * @brief The program execution begins here.
 * @param argc The number of command-line arguments.
 * @param argv The command line arguments.
 * @return 0 for normal program termination, -1 for abnormal termination.
 */
int main(int argc, char *argv[]) {
    // Check if the program is given command line arguments.
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " <students.txt>" << std::endl;
        return 1;
    }

    // Open the command line argument input file.
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cerr << "Input file " << argv[1] << " cannot be opened!" << std::endl;
        return 1;
    }

    std::vector<std::shared_ptr<Student>> gstudentPtrs;
    std::vector<std::shared_ptr<Student>> ugstudentPtrs;

    fillStudents(inFile, gstudentPtrs, ugstudentPtrs);
    inFile.close();

    std::cout << "The total number of students in the class = "
              << Student::getNumStudents() << std::endl << std::endl;

    std::cout << "UNDERGRADUATE STUDENT INFORMATION" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    printStudents(ugstudentPtrs);

    std::cout << "UNDERGRADUATE STUDENT STATISTICS" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    computeStatistics(ugstudentPtrs);

    std::cout << "GRADUATE STUDENT INFORMATION" << std::endl;
    std::cout << "----------------------------" << std::endl;
    printStudents(gstudentPtrs);

    std::cout << "GRADUATE STUDENT STATISTICS" << std::endl;
    std::cout << "---------------------------" << std::endl;
    computeStatistics(gstudentPtrs);

    return 0;
}
