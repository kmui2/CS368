///////////////////////////////////////////////////////////////////////////////
// File Name:      processStudent.cpp
//
// Author:         Kevin Mui
// CS email:       mui@cs.wisc.edu
//
// Description:    Methods to perform some processing on student objects.
///////////////////////////////////////////////////////////////////////////////

#include "processStudent.hpp"

// TODO: add other #include statements here, and using namespace std if desired

#include <sstream>
#include <iostream>
#include <map>
void fillStudents(std::istream &inFile,
                  std::vector<std::shared_ptr<Student>>& gstudentPtrs,
                  std::vector<std::shared_ptr<Student>>& ugstudentPtrs) {
    
    // get every student in file line by line                
    std::string line;
    while (inFile.good()) {
        getline(inFile, line);

        // split line by data
        std::stringstream ss;
        ss.str(line);
        std::string token;
        std::vector<std::string> data;
        while (std::getline(ss, token, ','))
            if (token.length() != 0)
                data.push_back(token);
        
        if (data.size() > 0) {
            // pase data element by element to form a student
            std::string name = data[1];
            std::vector<double> assignmentsScore;
            for (int i = 2; i <= 7; i++)
                assignmentsScore.push_back(std::stod(data[i]));
            double projectScore = std::stod(data[8]);
            // is undergrad
            if (data[0].compare("U") == 0) {
                std::string residenceHall = data[9];
                std::string yearInCollege = data[10];
                ugstudentPtrs.push_back(std::shared_ptr<Student>(
                    new UndergradStudent(name, assignmentsScore, projectScore, residenceHall, yearInCollege)));
            }
            // is grad
            else if (data[0].compare("G") == 0) {
                std::string researchArea = data[9];
                std::string advisor = data[10];
                gstudentPtrs.push_back(std::shared_ptr<Student>(
                    new GradStudent(name, assignmentsScore, projectScore, researchArea, advisor)));
            }
        }
    }

}

void printStudents(std::vector<std::shared_ptr<Student>>& students) {
    // prints details in every student
    for (auto it = students.begin(); it != students.end(); ++it) {
        it->get()->printDetails();
        std::cout << std::endl;
    }
}

void computeStatistics(std::vector<std::shared_ptr<Student>>& students) {

    // display the number of students (undergrad or grad)
    std::cout << "Number of students = " << students.size() << std::endl;

    // compute the mean of the total score.
    double sum = 0;
    for (auto it = students.begin(); it != students.end(); ++it)
        sum += it->get()->getTotal();
    std::cout << "The mean of the total score = " << sum / students.size() << std::endl;

    // sort and print the students based on their total.
    std::cout << "The sorted list of students (id, name, total, grade) in descending order of total:" << std::endl;
        // sort students using sorted map
    std::map<double, std::shared_ptr<Student>> sortedStudents;
    // print students 
      for (auto it = students.begin(); it != students.end(); ++it)
        sortedStudents[it->get()->getTotal()] = *it;
     // print students using reverse iterator on total grades
    for (auto it = sortedStudents.rbegin(); it != sortedStudents.rend(); ++it)
        std::cout << it->second->getId() << ", " << it->second->getName() << ", " 
                        << it->second->getTotal() << ", " << it->second->getGrade() << std::endl; 
    std::cout << std::endl;
}
