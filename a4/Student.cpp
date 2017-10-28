///////////////////////////////////////////////////////////////////////////////
// File Name:      Student.hpp
//
// Author:         Gerald, Isaac
// CS email:       gerald@cs.wisc.edu, isung@cs.wisc.edu
//
// Description:    The header file for the Student class.
//
// IMPORTANT NOTE: You should NOT add/modify/remove any PUBLIC methods.
//                 If you need, you may add some PRIVATE methods.
///////////////////////////////////////////////////////////////////////////////

#include "Student.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int Student::numStudents = 0;

/**
 * @brief A parameterised constructor for a Student.
 *
 * @param name Student's name.
 * @param assignmentsScore Student's assignment scores.
 * @param projectScore Student's project score.
 */
Student::Student(std::string name,
        std::vector<double> &assignmentsScore,
        double projectScore) {
            this->id = numStudents;
            this->name = name;
            this->assignmentsScore = assignmentsScore;
            this->projectScore = projectScore;
            numStudents++;
};

/**
 * @brief Getter for student's id.
 *
 * @return The id of the student.
 */
int Student::getId() {
    return id;
};

/**
 * @brief Getter for student's name.
 *
 * @return The name of the student.
 */
std::string Student::getName(){
    this->name;
};

/**
 * @brief Getter for student's assignment scores.
 *
 * @return A reference to the vector of student's assignment scores.
 */
std::vector<double>& Student::getAssignmentsScore() {
    this->assignmentsScore;
};

/**
 * @brief Getter for student's project score.
 *
 * @return The project score of the student.
 */
double Student::getProjectScore() {
    return this->projectScore;
};

/**
 * @brief Get the total number of students.
 *
 * @return The total number of students.
 */
int Student::getNumStudents(){
    return numStudents;
};

/**
 * @brief Prints the details of the student.
 *
 * @example This method prints the following details of a student.
 * STUDENT DETAILS:
 * Id = 2
 * Name = Joe Dart
 * Assignments = [67, 78, 96, 91, 97, 96]
 * Project = 96
 * Total = 90.05
 * Grade = CR
 */
void Student::printDetails(){
    std::cout << "STUDENT DETAILS:" << std::endl;
    std::cout << "Id = " << this->id << std::endl;
    std::cout << "Name = " << this->name << std::endl;
    std::string aStr = "[";
    std::vector<double> scores = Student::getAssignmentsScore();
    for (auto it = scores.begin(); it != scores.end(); ++it)
        aStr += std::to_string(*it)+",";
    std::cout << aStr.substr(0,aStr.size()-1) << "]" << std::endl;
    std::cout << "Project = " << this->projectScore << std::endl;
    std::cout << "Total = " << this->getTotal() << std::endl;
};

