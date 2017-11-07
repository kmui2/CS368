///////////////////////////////////////////////////////////////////////////////
// File Name:      GradStudent.cpp
//
// Author:         Gerald, Isaac, Kevin Mui
// CS email:       gerald@cs.wisc.edu, isung@cs.wisc.edu, mui@cs.wisc.edu
//
// Description:    The implmemntation for the GradStudent class.
///////////////////////////////////////////////////////////////////////////////

#include "GradStudent.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * @brief Constructor for a graduate student.
 *
 * @param name Graduate student's name.
 * @param assignmentsScore Graduate student's assignment scores.
 * @param projectScore Graduate student's project score.
 * @param researchArea Graduate student's research area.
 * @param advisor Graduate student's advisor.
 */
GradStudent::GradStudent(std::string name,
            std::vector<double>& assignmentsScore,
            double projectScore,
            std::string researchArea,
            std::string advisor)
            : Student(name, assignmentsScore, projectScore) {
                // set all data members
                this->researchArea = researchArea;
                this->advisor = advisor;
            };

/**
 * @brief Getter for the student's research area.
 *
 * @return The research area of the student.
 */
std::string GradStudent::getResearchArea() {
    return this->researchArea;
};

/**
 * @brief Getter for the student's advisor.
 *
 * @return The advisor of the student.
 */
std::string GradStudent::getAdvisor() {
    return this->advisor;
}

void GradStudent::printDetails() {
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
    std::cout << "Type = Graduate Student" << std::endl;
    std::cout << "Research Area = " << this->researchArea << std::endl;
    std::cout << "Advisor = " << this->advisor << std::endl;
    // std::cout << std::endl;
};

double GradStudent::getTotal() {
    // sum up all assignment scores then calculate weighted mean with project score
    std::vector<double> scores = Student::getAssignmentsScore();
    double avg_assginments_score = std::accumulate(scores.begin(), scores.end(), 0.0)/scores.size();
    return avg_assginments_score * 0.5 + Student::getProjectScore() * 0.5;
};

std::string GradStudent::getGrade(){
    // gets credit if total >= 80
    return this->getTotal() >= 80 ? "CR" : "N";
}

