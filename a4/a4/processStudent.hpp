///////////////////////////////////////////////////////////////////////////////
// File Name:      processStudent.hpp
//
// Author:         Gerald, Varun, Isaac
// CS email:       gerald@cs.wisc.edu, vnaik@cs.wisc.edu, isung@cs.wisc.edu
//
// Description:    Methods to perform some processing on student objects.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#ifndef A4_PROCESSSTUDENT_HPP
#define A4_PROCESSSTUDENT_HPP

#include "GradStudent.hpp"
#include "UndergradStudent.hpp"

#include <memory>
#include <istream>
#include <vector>

/**
 * @brief Read students' data from an input file and store them in 2 vectors
 *        based on the type of the student.
 *
 * @param inFile The input file with students' data.
 * @param gstudentPtrs Vector of shared_ptrs to graduate students.
 * @param ugstudentPtrs Vector of shared_ptrs to undergraduate students.
 */
void fillStudents(std::istream &inFile,
                  std::vector<std::shared_ptr<Student>>& gstudentPtrs,
                  std::vector<std::shared_ptr<Student>>& ugstudentPtrs);

/**
 * @brief Prints the details of a group of students.
 *
 * @param students A vector of student shared_ptrs to be printed.
 */
void printStudents(std::vector<std::shared_ptr<Student>>& students);

/**
 * @brief Computes the statistics like number of students, mean of total score, and
 *        the sorted list of students in descending order based on their total.
 *
 * @param students A vector of student shared_ptrs for which the statistics needs to computed.
 */
void computeStatistics(std::vector<std::shared_ptr<Student>>& students);

#endif //A4_PROCESSSTUDENT_HPP
