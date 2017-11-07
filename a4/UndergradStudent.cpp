///////////////////////////////////////////////////////////////////////////////
// File Name:      UndergradStudent.cpp
//
// Author:         Gerald, Isaac, Kevin Mui
// CS email:       gerald@cs.wisc.edu, isung@cs.wisc.edu, mui@cs.wisc.edu
//
// Description:    The implmemntation for the UndergradStudent class.
//
///////////////////////////////////////////////////////////////////////////////

#include "UndergradStudent.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * @brief Constructor for an undergraduate student.
 *
 * @param name Undergraduate student's name
 * @param assignmentsScore Undergraduate student's assignment scores.
 * @param projectScore Undergraduate student's project score.
 * @param residenceHall Undergraduate student's residence hall.
 * @param yearInCollege Undergraduate student's year in college.
 */
UndergradStudent::UndergradStudent(std::string name,
                    std::vector<double> &assignmentsScore,
                    double projectScore,
                    std::string residenceHall,
                    std::string yearInCollege)
                    : Student(name, assignmentsScore, projectScore) {
                        // set all data members
                        this->residenceHall = residenceHall;
                        this->yearInCollege = yearInCollege;
                };

/**
 * @brief Getter for a student's residence hall.
 *
 * @return The residence hall in which the student resides.
 */
std::string UndergradStudent::getResidenceHall() {
    return this->residenceHall;
};

/**
 * @brief Getter for a student's year in college.
 *
 * @return The year in college of the student.
 */
std::string UndergradStudent::getYearInCollege() {
    return this->yearInCollege;
};

void UndergradStudent::printDetails() {
    std::cout << "STUDENT DETAILS:" << std::endl;
    std::cout << "Id = " << Student::getId() << std::endl;
    std::cout << "Name = " << Student::getName() << std::endl;
    // get assignments and print scores neatly
    std::cout << "Assignments = [";
    std::vector<double> scores = Student::getAssignmentsScore();
    for (int i = 0; i < scores.size(); i++)
        // print score double and ending with either , not at the end or ] at the end
        std::cout << scores[i] << ((i != scores.size()-1) ? ", " : "]");
    std::cout << std::endl;
    std::cout << "Project = " << Student::getProjectScore() << std::endl;
    std::cout << "Total = " << this->getTotal() << std::endl;
    std::cout << "Grade = " << this->getGrade() << std::endl;
    std::cout << "Type = Undergraduate Student" << std::endl;
    std::cout << "Residence Hall = " << this->residenceHall << std::endl;
    std::cout << "Year in College = " << this->yearInCollege << std::endl;
    // std::cout << std::endl;
};

double UndergradStudent::getTotal() {
    // sum up all assignment scores then calculate weighted mean with project score
    std::vector<double> scores = Student::getAssignmentsScore();
    double avg_assginments_score = std::accumulate(scores.begin(), scores.end(), 0.0)/scores.size();
    return avg_assginments_score * 0.7 + Student::getProjectScore() * 0.3;
};

std::string UndergradStudent::getGrade() {
    // gets credit if total >= 70
    return this->getTotal() >= 70 ? "CR" : "N";
};

