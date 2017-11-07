///////////////////////////////////////////////////////////////////////////////
// File Name:      test.c
//
// Author:         Varun Naik
// CS email:       vnaik@cs.wisc.edu
//
// Description:    Unit tests for a4. As a reminder, even if you pass all of
//                 these tests, you are not yet guaranteed 90/90 on the
//                 autograder portion. But if you do not pass these tests, you
//                 will probably receive a very low score on the autograder.
//                 We named this file test.c rather than test.cpp so that you
//                 can still compile your code with `g++ -std=c++11 *.cpp`.
//
// Sources:        Google Test, cppreference.com
//
// URL(s) of sources:
//                 https://github.com/google/googletest
//                 http://en.cppreference.com/w/
///////////////////////////////////////////////////////////////////////////////

#include "GradStudent.hpp"
#include "processStudent.hpp"
#include "UndergradStudent.hpp"

#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * @brief A dummy subclass of Student for testing purposes.
 *
 * Normally, the implementation of each method would be in a separate file. We
 * put everything in here to be concise - we only want one test file with C++
 * code.
 */
class TestStudent : public Student {
public:
    // Inherit Student constructor(s)
    using Student::Student;

    /**
     * @brief Dummy version of getTotal().
     */
    virtual double getTotal() override {
        return 0.0;
    }

    /**
     * @brief Dummy version of getTotal().
     */
    virtual std::string getGrade() override {
        return "";
    }
};

/**
 * @brief Compile-time checks for the Student class. This function is never
 *        called, but it should compile without any errors.
 */
void compilerChecks() {
    // Not a comprehensive check of each pure virtual method.
    static_assert(
        std::is_abstract<Student>::value,
        "Student class is not abstract"
    );

    // A student asked on Piazza if they can add constructors. No need to check
    // the provided constructor - the test cases effectively do that. This
    // check is not comprehensive.
    static_assert(
        not std::is_default_constructible<TestStudent>::value,
        "Student class should not define a zero-argument constructor"
    );

    // If the return types in the Student class have changed, do not compile.
    // No need to check exact prototypes - the test cases effectively do that.
    static_assert(
        std::is_same<int, decltype(std::declval<Student>().getId())>::value,
        "Student::getId() return type is not int"
    );
    static_assert(
        std::is_same<std::string, decltype(std::declval<Student>().getName())>::value,
        "Student::getName() return type is not std::string"
    );
    static_assert(
        std::is_same<
            std::vector<double> &,
            decltype(std::declval<Student>().getAssignmentsScore())
        >::value,
        "Student::getAssignmentsScore() return type is not const std::vector<double> &"
    );
    static_assert(
        std::is_same<double, decltype(std::declval<Student>().getProjectScore())>::value,
        "Student::getProjectScore() return type is not double"
    );
    static_assert(
        std::is_same<int, decltype(Student::getNumStudents())>::value,
        "Student::getNumStudents() return type is not int"
    );
    static_assert(
        std::is_same<void, decltype(std::declval<Student>().printDetails())>::value,
        "Student::printDetails() return type is not void"
    );
    static_assert(
        std::is_same<double, decltype(std::declval<Student>().getTotal())>::value,
        "Student::getTotal() return type is not double"
    );
    static_assert(
        std::is_same<std::string, decltype(std::declval<Student>().getGrade())>::value,
        "Student::getGrade() return type is not std::string"
    );
}

/**
 * @brief Helper function that returns an AssertionResult for ASSERT_OPEN.
 *
 * Do not call this function directly. Call ASSERT_OPEN instead.
 *
 * @param expr0 The first expression passed to ASSERT_OPEN
 * @param inFile See "file" argument for ASSERT_OPEN
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult assertOpen(const std::string &expr0, std::ifstream &inFile) {
    if (inFile.is_open()) {
        return ::testing::AssertionSuccess();
    } else {
        return ::testing::AssertionFailure() << "Expected " << expr0 << " to be open";
    }
}

/**
 * @brief Helper function that returns an AssertionResult for ASSERT_OPEN.
 *
 * Do not call this function directly. Call ASSERT_OPEN instead.
 *
 * @param expr0 The first expression passed to ASSERT_OPEN
 * @param outFile See "file" argument for ASSERT_OPEN
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult assertOpen(const std::string &expr0, std::ofstream &outFile) {
    if (outFile.is_open()) {
        return ::testing::AssertionSuccess();
    } else {
        return ::testing::AssertionFailure() << "Expected " << expr0 << " to be open";
    }
}

/**
 * @brief Raises a fatal failure with the correct line number if file is not
 *        open.
 *
 * @param file The input or output file
 */
#define ASSERT_OPEN(file) \
    ASSERT_PRED_FORMAT1(assertOpen, file)

/**
 * @brief Helper function that returns an AssertionResult for EXPECT_EOF.
 *
 * Do not call this function directly. Call EXPECT_EOF instead.
 *
 * @param expr0 The first expression passed to EXPECT_EOF
 * @param inFile See comment for EXPECT_EOF
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult expectEof(const std::string &expr0, std::istream &inFile) {
    if (inFile.eof()) {
        return ::testing::AssertionSuccess();
    } else {
        return ::testing::AssertionFailure() << "Expected " << expr0 << " to be at EOF";
    }
}

/**
 * @brief Raises a non-fatal failure with the correct line number if inFile has
 *        not reached EOF.
 *
 * @param inFile The input file
 */
#define EXPECT_EOF(inFile) \
    EXPECT_PRED_FORMAT1(expectEof, inFile)

/**
 * @brief Helper function that returns an AssertionResult for ASSERT_NOT_FAILED.
 *
 * Do not call this function directly. Call ASSERT_NOT_FAILED instead.
 *
 * @param expr0 The first expression passed to ASSERT_NOT_FAILED
 * @param outFile See comment for ASSERT_NOT_FAILED
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult assertNotFailed(const std::string &expr0, std::ofstream &outFile) {
    if (outFile.fail()) {
        return ::testing::AssertionFailure()
            << "Expected " << expr0 << " to be in a non-failed state";
    } else {
        return ::testing::AssertionSuccess();
    }
}

/**
 * @brief Raises a fatal failure with the correct line number if outFile is in
 *        a failed state.
 *
 * @param outFile The output file
 */
#define ASSERT_NOT_FAILED(outFile) \
    ASSERT_PRED_FORMAT1(assertNotFailed, outFile)

/**
 * @brief Empties the contents of the buffer, and clears its error state flags.
 *
 * @param buff The buffer containing the lines written to cout
 */
void clearBuff(std::stringstream &buff) {
    buff.str("");
    buff.clear();
}

/**
 * @brief Helper function that returns an AssertionResult for MATCH_NEXT_LINE.
 *
 * Do not call this function directly. Call MATCH_NEXT_LINE instead.
 *
 * @param expr0 The first expression passed to MATCH_NEXT_LINE
 * @param expr1 The second expression passed to MATCH_NEXT_LINE
 * @param buff See comment for MATCH_NEXT_LINE
 * @param str See comment for MATCH_NEXT_LINE
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult matchNextLine(const std::string &expr0,
                                         const std::string &expr1,
                                         std::stringstream &buff,
                                         const std::string &str) {
    std::string line;
    std::getline(buff, line);
    if (buff.eof()) {
        return ::testing::AssertionFailure()
            << "Line printed to cout is incorrect" << std::endl
            << " Printed: (end of printed output)" << std::endl
            << "Expected: \"" << str << "\"";
    } else {
        if (line == str) {
            return ::testing::AssertionSuccess();
        } else {
            return ::testing::AssertionFailure()
                << "Line printed to cout is incorrect" << std::endl
                << " Printed: \"" << line << "\"" << std::endl
                << "Expected: \"" << str << "\"";
        }
    }
}

/**
 * @brief Reads the next line from buff and checks that it is equal to str.
 *        Raises a non-fatal failure with the correct line number if we have
 *        reached the end of file, or if the pattern does not match.
 *
 * @param buff The buffer containing the lines written to cout
 * @param str The exact string to compare to
 */
#define MATCH_NEXT_LINE(buff, str) \
    EXPECT_PRED_FORMAT2(matchNextLine, buff, str)

/**
 * @brief Helper function that returns an AssertionResult for MATCH_END.
 *
 * Do not call this function directly. Call MATCH_END instead.
 *
 * @param expr0 The first expression passed to MATCH_END
 * @param buff See comment for MATCH_END
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult matchEnd(const std::string &expr0, std::stringstream &buff) {
    std::string line;
    getline(buff, line);
    if (buff.eof()) {
        return ::testing::AssertionSuccess();
    } else {
        return ::testing::AssertionFailure()
            << "Line printed to cout is incorrect" << std::endl
            << " Printed: \"" << line << "\"" << std::endl
            << "Expected: (end of printed output)";
    }
}

/**
 * @brief Reads the next line from buff and checks that the end of the stream
 *        has been reached. Raises a non-fatal failure with the correct line
 *        number otherwise.
 *
 * @param buff The buffer containing the lines written to cout
 */
#define MATCH_END(buff) \
    EXPECT_PRED_FORMAT1(matchEnd, buff)

/**
 * @brief A test fixture class for all a4 tests.
 *
 * Again, the implementation of each method is in the same file.
 */
class A4Test : public ::testing::Test {
protected:
    std::stringstream buff;
    // cout_buff is a pointer. Don't worry, we will cover this later in the semester.
    std::streambuf *cout_buff;

    /**
     * @brief Code to run before each unit test.
     *
     * Redirects std::cout to the in-memory variable buff.
     * See: http://en.cppreference.com/w/cpp/io/basic_ios/rdbuf
     */
    virtual void SetUp() override {
        cout_buff = std::cout.rdbuf(buff.rdbuf());
    }

    /**
     * @brief Code to run after each unit test.
     *
     * Resets std::cout so that calls to cout print to the screen again.
     */
    virtual void TearDown() override {
        std::cout.rdbuf(cout_buff);
    }
};

/**
 * @brief Test case for Student. Makes sure the Student methods do not crash.
 */
TEST_F(A4Test, BasicStudentTest) {
    // Set up TestStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    TestStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0
    );

    // Call Student methods
    student.getId();
    student.getName();
    student.getAssignmentsScore();
    student.getProjectScore();

    // Call static methods
    Student::getNumStudents();
}

/**
 * @brief Test case for UndergradStudent. Makes sure the UndergradStudent
 *        methods do not crash.
 */
TEST_F(A4Test, BasicUndergradStudentTest) {
    // Set up UndergradStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    UndergradStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0,
        "Sellery",
        "Senior"
    );

    // Call Student methods
    student.getId();
    student.getName();
    student.getAssignmentsScore();
    student.getProjectScore();

    // Call UndergradStudent methods
    student.getResidenceHall();
    student.getYearInCollege();
    student.printDetails();
    student.getTotal();
    student.getGrade();

    // Call static methods
    Student::getNumStudents();
    UndergradStudent::getNumStudents();
}

/**
 * @brief Test case for GradStudent. Makes sure the GradStudent methods do not
 *        crash.
 */
TEST_F(A4Test, BasicGradStudentTest) {
    // Set up GradStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    GradStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0,
        "Databases",
        "Adalbert Gerald Soosai Raj"
    );

    // Call Student methods
    student.getId();
    student.getName();
    student.getAssignmentsScore();
    student.getProjectScore();

    // Call GradStudent methods
    student.getResearchArea();
    student.getAdvisor();
    student.printDetails();
    student.getTotal();
    student.getGrade();

    // Call static methods
    Student::getNumStudents();
    GradStudent::getNumStudents();
}

/**
 * @brief Test case for processStudent.cpp. Makes sure the functions in the
 *        file do not crash. Performs best-effort cleanup of modified files.
 */
TEST_F(A4Test, BasicProcessStudentTest) {
    // Make sure the students file has the correct contents
    std::ofstream outFile("testStudents.txt");
    ASSERT_OPEN(outFile) << "Cannot open testStudents.txt for output";
    outFile << "G,Mark Lettieri,67,90,83,96,87,95,98,Guitar Studies,Wes Montgomery" << std::endl;
    outFile << "U,Antwaun Stanley,67,96,83,76,60,99,89,Waters,Sophomore" << std::endl;
    outFile << "U,Joe Dart,93,67,78,96,91,97,96,Sellery,Senior" << std::endl;
    outFile << "G,Michael League,54,77,89,75,90,87,91,School of Funk,Bootsy Collins" << std::endl;

    ASSERT_NOT_FAILED(outFile) << "Error writing to testStudents.txt";
    outFile.close();

    // Open the students.txt input file.
    std::ifstream inFile("testStudents.txt");
    ASSERT_OPEN(inFile) << "Cannot open testStudents.txt for input";

    std::vector<std::shared_ptr<Student>> gstudentPtrs;
    std::vector<std::shared_ptr<Student>> ugstudentPtrs;

    // Call fillStudents()
    fillStudents(inFile, gstudentPtrs, ugstudentPtrs);
    inFile.close();
    std::remove("testStudents.txt");

    // Call printStudents() and computeStatistics() for undergrads
    printStudents(ugstudentPtrs);
    computeStatistics(ugstudentPtrs); 

    // Call printStudents() and computeStatistics() for grads
    printStudents(gstudentPtrs);
    computeStatistics(gstudentPtrs);    
}

/**
 * @brief Test case for Student. Makes sure the Student methods behave as
 *        desired.
 */
TEST_F(A4Test, AdvancedStudentTest) {
    // Set up TestStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    TestStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0
    );

    // Call Student methods
    EXPECT_EQ(student.getId(), 0);
    EXPECT_EQ(student.getName(), "Varun Naik");
    const std::vector<double> assignmentsScore = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    EXPECT_EQ(student.getAssignmentsScore(), assignmentsScore);
    EXPECT_EQ(student.getProjectScore(), 100.0);

    // Call static methods
    EXPECT_EQ(Student::getNumStudents(), 1);

    MATCH_END(buff);
    clearBuff(buff);
}

/**
 * @brief Test case for UndergradStudent. Makes sure the UndergradStudent
 *        methods behave as desired.
 */
TEST_F(A4Test, AdvancedUndergradStudentTest) {
    // Set up UndergradStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    UndergradStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0,
        "Sellery",
        "Senior"
    );

    // Call Student methods
    EXPECT_EQ(student.getId(), 0);
    EXPECT_EQ(student.getName(), "Varun Naik");
    const std::vector<double> assignmentsScore = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    EXPECT_EQ(student.getAssignmentsScore(), assignmentsScore);
    EXPECT_EQ(student.getProjectScore(), 100.0);

    // Call UndergradStudent methods
    EXPECT_EQ(student.getResidenceHall(), "Sellery");
    EXPECT_EQ(student.getYearInCollege(), "Senior");

    MATCH_END(buff);
    clearBuff(buff);

    student.printDetails();
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 0");
    MATCH_NEXT_LINE(buff, "Name = Varun Naik");
    MATCH_NEXT_LINE(buff, "Assignments = [90, 94, 92, 97, 98, 99]");
    MATCH_NEXT_LINE(buff, "Project = 100");
    MATCH_NEXT_LINE(buff, "Total = 96.5");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Undergraduate Student");
    MATCH_NEXT_LINE(buff, "Residence Hall = Sellery");
    MATCH_NEXT_LINE(buff, "Year in College = Senior");
    MATCH_END(buff);
    clearBuff(buff);

    EXPECT_NEAR(student.getTotal(), 96.5, 0.000001);
    EXPECT_EQ(student.getGrade(), "CR");

    // Call static methods
    EXPECT_EQ(Student::getNumStudents(), 1);
    EXPECT_EQ(UndergradStudent::getNumStudents(), 1);

    MATCH_END(buff);
    clearBuff(buff);
}

/**
 * @brief Test case for GradStudent. Makes sure the GradStudent methods behave
 *        as desired.
 */
TEST_F(A4Test, AdvancedGradStudentTest) {
    // Set up GradStudent object
    double assignScore[] = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    std::vector<double> assignScoreVec (assignScore, assignScore + sizeof(assignScore) / sizeof(double) );

    GradStudent student(
        "Varun Naik",
        assignScoreVec,
        100.0,
        "Databases",
        "Adalbert Gerald Soosai Raj"
    );

    // Call Student methods
    EXPECT_EQ(student.getId(), 0);
    EXPECT_EQ(student.getName(), "Varun Naik");
    const std::vector<double> assignmentsScore = { 90.0, 94.0, 92.0, 97.0, 98.0, 99.0 };
    EXPECT_EQ(student.getAssignmentsScore(), assignmentsScore);
    EXPECT_EQ(student.getProjectScore(), 100.0);

    // Call GradStudent methods
    EXPECT_EQ(student.getResearchArea(), "Databases");
    EXPECT_EQ(student.getAdvisor(), "Adalbert Gerald Soosai Raj");

    MATCH_END(buff);
    clearBuff(buff);

    student.printDetails();
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 0");
    MATCH_NEXT_LINE(buff, "Name = Varun Naik");
    MATCH_NEXT_LINE(buff, "Assignments = [90, 94, 92, 97, 98, 99]");
    MATCH_NEXT_LINE(buff, "Project = 100");
    MATCH_NEXT_LINE(buff, "Total = 97.5");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Graduate Student");
    MATCH_NEXT_LINE(buff, "Research Area = Databases");
    MATCH_NEXT_LINE(buff, "Advisor = Adalbert Gerald Soosai Raj");
    MATCH_END(buff);
    clearBuff(buff);

    EXPECT_NEAR(student.getTotal(), 97.5, 0.000001);
    EXPECT_EQ(student.getGrade(), "CR");

    // Call static methods
    EXPECT_EQ(Student::getNumStudents(), 1);
    EXPECT_EQ(GradStudent::getNumStudents(), 1);

    MATCH_END(buff);
    clearBuff(buff);
}

/**
 * @brief Test case for processStudent.cpp. Makes sure the functions in the
 *        file behave as desired. Performs best-effort cleanup of modified files.
 */
TEST_F(A4Test, AdvancedProcessStudentTest) {
    // Make sure the students file has the correct contents
    std::ofstream outFile("testStudents.txt");
    ASSERT_OPEN(outFile) << "Cannot open testStudents.txt for output";
    outFile << "G,Mark Lettieri,67,90,83,96,87,95,98,Guitar Studies,Wes Montgomery" << std::endl;
    outFile << "U,Antwaun Stanley,67,96,83,76,60,99,89,Waters,Sophomore" << std::endl;
    outFile << "U,Joe Dart,93,67,78,96,91,97,96,Sellery,Senior" << std::endl;
    outFile << "G,Michael League,54,77,89,75,90,87,91,School of Funk,Bootsy Collins" << std::endl;
    ASSERT_NOT_FAILED(outFile) << "Error writing to testStudents.txt";
    outFile.close();

    // Open the students.txt input file.
    std::ifstream inFile("testStudents.txt");
    ASSERT_OPEN(inFile) << "Cannot open testStudents.txt for input";

    std::vector<std::shared_ptr<Student>> gstudentPtrs;
    std::vector<std::shared_ptr<Student>> ugstudentPtrs;

    // Call fillStudents()
    fillStudents(inFile, gstudentPtrs, ugstudentPtrs);    
    EXPECT_EQ(Student::getNumStudents(), 4);
    EXPECT_EQ(ugstudentPtrs.size(), 2);    
    EXPECT_EQ(gstudentPtrs.size(), 2);
    EXPECT_EOF(inFile) << "fillStudents() does not read all lines in inFile";
    inFile.close();
    std::remove("testStudents.txt");

    MATCH_END(buff);
    clearBuff(buff);

    // Call printStudents() and computeStatistics() for undergrads
    printStudents(ugstudentPtrs);
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 1");
    MATCH_NEXT_LINE(buff, "Name = Antwaun Stanley");
    MATCH_NEXT_LINE(buff, "Assignments = [67, 96, 83, 76, 60, 99]");
    MATCH_NEXT_LINE(buff, "Project = 89");
    MATCH_NEXT_LINE(buff, "Total = 82.8167");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Undergraduate Student");
    MATCH_NEXT_LINE(buff, "Residence Hall = Waters");
    MATCH_NEXT_LINE(buff, "Year in College = Sophomore");
    MATCH_NEXT_LINE(buff, "");
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 2");
    MATCH_NEXT_LINE(buff, "Name = Joe Dart");
    MATCH_NEXT_LINE(buff, "Assignments = [93, 67, 78, 96, 91, 97]");
    MATCH_NEXT_LINE(buff, "Project = 96");
    MATCH_NEXT_LINE(buff, "Total = 89.7");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Undergraduate Student");
    MATCH_NEXT_LINE(buff, "Residence Hall = Sellery");
    MATCH_NEXT_LINE(buff, "Year in College = Senior");
    MATCH_NEXT_LINE(buff, "");
    MATCH_END(buff);
    clearBuff(buff);

    computeStatistics(ugstudentPtrs);
    MATCH_NEXT_LINE(buff, "Number of students = 2");
    MATCH_NEXT_LINE(buff, "The mean of the total score = 86.2583");
    MATCH_NEXT_LINE(buff,
        "The sorted list of students (id, name, total, grade) in descending order of total:");
    MATCH_NEXT_LINE(buff, "2, Joe Dart, 89.7, CR");
    MATCH_NEXT_LINE(buff, "1, Antwaun Stanley, 82.8167, CR");
    MATCH_NEXT_LINE(buff, "");
    MATCH_END(buff);
    clearBuff(buff);
    EXPECT_EQ(ugstudentPtrs.size(), 2);
    int uid0 = ugstudentPtrs[0]->getId();
    int uid1 = ugstudentPtrs[1]->getId();    
    std::cout << uid0 << std::endl;
    std::cout << uid1 << std::endl;
    ASSERT_TRUE(uid0 == 2 and uid1 == 1)
        << "ugstudentPtrs is not sorted in decreasing order by total";

    // Call printStudents() and computeStatistics() for grads
    printStudents(gstudentPtrs);
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 0");
    MATCH_NEXT_LINE(buff, "Name = Mark Lettieri");
    MATCH_NEXT_LINE(buff, "Assignments = [67, 90, 83, 96, 87, 95]");
    MATCH_NEXT_LINE(buff, "Project = 98");
    MATCH_NEXT_LINE(buff, "Total = 92.1667");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Graduate Student");
    MATCH_NEXT_LINE(buff, "Research Area = Guitar Studies");
    MATCH_NEXT_LINE(buff, "Advisor = Wes Montgomery");
    MATCH_NEXT_LINE(buff, "");
    MATCH_NEXT_LINE(buff, "STUDENT DETAILS:");
    MATCH_NEXT_LINE(buff, "Id = 3");
    MATCH_NEXT_LINE(buff, "Name = Michael League");
    MATCH_NEXT_LINE(buff, "Assignments = [54, 77, 89, 75, 90, 87]");
    MATCH_NEXT_LINE(buff, "Project = 91");
    MATCH_NEXT_LINE(buff, "Total = 84.8333");
    MATCH_NEXT_LINE(buff, "Grade = CR");
    MATCH_NEXT_LINE(buff, "Type = Graduate Student");
    MATCH_NEXT_LINE(buff, "Research Area = School of Funk");
    MATCH_NEXT_LINE(buff, "Advisor = Bootsy Collins");
    MATCH_NEXT_LINE(buff, "");
    MATCH_END(buff);
    clearBuff(buff);

    computeStatistics(gstudentPtrs);
    MATCH_NEXT_LINE(buff, "Number of students = 2");
    MATCH_NEXT_LINE(buff, "The mean of the total score = 88.5");
    MATCH_NEXT_LINE(buff,
        "The sorted list of students (id, name, total, grade) in descending order of total:");
    MATCH_NEXT_LINE(buff, "0, Mark Lettieri, 92.1667, CR");
    MATCH_NEXT_LINE(buff, "3, Michael League, 84.8333, CR");
    MATCH_NEXT_LINE(buff, "");
    MATCH_END(buff);
    clearBuff(buff);
    EXPECT_EQ(gstudentPtrs.size(), 2);
    int gid0 = gstudentPtrs[0]->getId();
    int gid1 = gstudentPtrs[1]->getId();
    ASSERT_TRUE(gid0 == 0 and gid1 == 3)
        << "gstudentPtrs is not sorted in decreasing order by total";
}

/**
 * @brief Unit test execution begins here.
 *
 * @param argc Number of command-line arguments
 * @param argv Command line arguments
 * @return 0 for normal program termination, other error code for abnormal termination
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
