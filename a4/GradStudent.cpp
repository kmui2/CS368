///////////////////////////////////////////////////////////////////////////////
// File Name:      GradStudent.hpp
//
// Author:         Gerald, Isaac, Varun
// CS email:       gerald@cs.wisc.edu, isung@cs.wisc.edu, vnaik@cs.wisc.edu
//
// Description:    The header file for the GradStudent class.
//
// IMPORTANT NOTE: This file should NOT be modified.
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
    std::string aStr = "[";
    std::vector<double> scores = Student::getAssignmentsScore();
    for (auto it = scores.begin(); it != scores.end(); ++it)
        aStr += std::to_string(*it)+",";
    std::cout << aStr.substr(0,aStr.size()-1) << "]" << std::endl;
    std::cout << "Project = " << Student::getProjectScore() << std::endl;
    std::cout << "Total = " << this->getTotal() << std::endl;
    std::cout << "Grade = " << this->getGrade() << std::endl;
    std::cout << "Type = Graduate Student" << std::endl;
    std::cout << "Research Area = " << this->researchArea << std::endl;
    std::cout << "Advisor = " << this->advisor << std::endl;
};

double GradStudent::getTotal() {
    std::vector<double> scores = Student::getAssignmentsScore();
    double avg_assginments_score = std::accumulate(scores.begin(), scores.end(), 0.0)/scores.size();
    return avg_assginments_score * 0.5 + Student::getProjectScore() * 0.5;
};

std::string GradStudent::getGrade(){
    return this->getTotal() >= 80 ? "CR" : "N";
}

