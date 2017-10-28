///////////////////////////////////////////////////////////////////////////////
// File Name:      processStudent.cpp
//
// Author:         <your name>
// CS email:       <your CS email>
//
// Description:    Methods to perform some processing on student objects.
//
// Sources:        <Sources, if any>
//
// URL(s) of sources:
//                 <URLs of your sources, if any>
///////////////////////////////////////////////////////////////////////////////

#include "processStudent.hpp"

// TODO: add other #include statements here, and using namespace std if desired

#include <sstream>
#include <iostream>
void fillStudents(std::istream &inFile,
                  std::vector<std::shared_ptr<Student>>& gstudentPtrs,
                  std::vector<std::shared_ptr<Student>>& ugstudentPtrs) {

    // TODO: Implement this method.
    std::string line;
    while (inFile.good()) {
        getline(inFile, line);
        std::stringstream ss;
        ss.str(line);
        std::string token;
        std::vector<std::string> data;
        while (std::getline(ss, token, ',')) {
            if (token.length() != 0) {
                data.push_back(token);
            }
        }
        if (data.size() > 0) {
            std::string name = data[1];
            std::vector<double> assignmentsScore;
            for (int i = 2; i <= 7; i++) {
                assignmentsScore.push_back(std::stod(data[i]));
            }
            double projectScore = std::stod(data[8]);
            if (data[0].compare("U") == 0) {
                std::string residenceHall = data[9];
                std::string yearInCollege = data[10];
                ugstudentPtrs.push_back(std::shared_ptr<Student>(new UndergradStudent(name, assignmentsScore, projectScore, residenceHall, yearInCollege)));
            }
            else if (data[0].compare("G") == 0) {
                std::string researchArea = data[9];
                std::string advisor = data[10];
                gstudentPtrs.push_back(std::shared_ptr<Student>(new GradStudent(name, assignmentsScore, projectScore, researchArea, advisor)));
            }
        }
        
    }

}

void printStudents(std::vector<std::shared_ptr<Student>>& students) {

    // TODO: Implement this method.
    for (auto it = students.begin(); it != students.end(); ++it) {
        it->get()->printDetails();
    }

}

void computeStatistics(std::vector<std::shared_ptr<Student>>& students) {

    // TODO: Implement this method.

    // display the number of students (undergrad or grad)

    // compute the mean of the total score.

    // sort and print the students based on their total.
}
