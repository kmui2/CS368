///////////////////////////////////////////////////////////////////////////////
// File Name:      test.c
//
// Author:         Varun Naik
// CS email:       vnaik@cs.wisc.edu
//
// Description:    Unit tests for a5. As a reminder, even if you pass all of
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

#include "SmartInteger.hpp"

#include "gtest/gtest.h"

#include <exception>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * @brief Compile-time checks for the SmartInteger class. This function is never
 *        called, but it should compile without any errors.
 */
void compilerChecks() {
    // If casting operator is overloaded, it could interfere with the autograder
    static_assert(
        not std::is_convertible<SmartInteger, int>::value,
        "SmartInteger should not be implicitly convertible to int"
    );

    static_assert(
        std::is_same<int, decltype(std::declval<SmartInteger>().getValue())>::value,
        "SmartInteger::getValue() return type is not int"
    );
}

/**
 * @brief Returns true if expr, after stripping const and references, is the
 *        same as returnType. Both expr and returnType are only used in an
 *        unevaluated context.
 *
 * @param expr The expression whose return type is compared
 * @param returnType The desired return type
 */
#define HAS_STRIPPED_RETURN_TYPE(expr, returnType) \
    (std::is_same< \
        returnType, \
        std::remove_const<std::remove_reference<decltype(expr)>::type>::type \
    >::value)

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
 * @brief Helper function that returns an AssertionResult for
 *        EXPECT_NOT_ASSIGNABLE.
 *
 * Do not call this function directly. Call EXPECT_NOT_ASSIGNABLE instead.
 *
 * @param expr0 The call to std::is_assignable
 * @param isAssignable The result of the call to std::is_assignable
 * @return AssertionSuccess() on success or AssertionFailure() on failure
 */
::testing::AssertionResult expectNotAssignable(const std::string &expr0,
                                               bool isAssignable) {
    if (isAssignable) {
        return ::testing::AssertionFailure()
            << "  Actual: the assignment statement compiles" << std::endl
            << "Expected: the assignment statement should not compile";
    } else {
        return ::testing::AssertionSuccess();
    }
}

/**
 * @brief Checks whether lhs can be assigned to rhsType. lhs is only used in
 *        an unevaluated context. Raises a non-fatal failure with the correct
 *        line number if the assignment fails.
 *
 * @param lhs The left-hand side of the assignment
 * @param rhsType The type of the right-hand side of the assignment
 */
#define EXPECT_NOT_ASSIGNABLE(lhs, rhsType) \
    EXPECT_PRED_FORMAT1(expectNotAssignable, (std::is_assignable<decltype(lhs), rhsType>::value))

/**
 * @brief Checks whether SmartInteger lhs has the same value as int rhs.
 *        Raises a non-fatal failure with the correct line number if the two
 *        have different values.
 *
 * Ideally, the code would go in a helper function that takes a SmartInteger
 * and an int as arguments. But it is impossible to call EXPECT_EQ from a
 * function that returns non-void.
 *
 * @param lhs The SmartInteger, which is internally converted to an int
 * @param rhs The int to compare to
 */
#define EXPECT_SMARTINTEGER_EQ(lhs, rhs) \
    do { \
        static_assert(HAS_STRIPPED_RETURN_TYPE(lhs, SmartInteger), "lhs is not a SmartInteger"); \
        static_assert(HAS_STRIPPED_RETURN_TYPE(rhs, int), "rhs is not an int"); \
        try { \
            EXPECT_EQ((lhs).getValue(), rhs); \
        } catch (...) { \
            ADD_FAILURE() \
                << "Expected: (" #lhs ").getValue() doesn't throw an exception." \
                << std::endl \
                << "  Actual: it throws." << std::endl; \
        } \
    } while (0)

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
 * @brief A test fixture class for all a5 tests.
 *
 * Normally, the implementation of each method would be in a separate file. We
 * put everything in here to be concise - we only want one test file with C++
 * code.
 */
class A5Test : public ::testing::Test {
protected:
    /**
     * @brief Code to run before each unit test.
     */
    virtual void SetUp() override {
        // No code
    }

    /**
     * @brief Code to run after each unit test.
     */
    virtual void TearDown() override {
        // No code
    }
};

#ifdef RunConstructorBasicTest

/**
 * @brief Test case to make sure the constructor and getValue() behave as
 *        desired.
 */
TEST_F(A5Test, ConstructorBasicTest) {
    SmartInteger n1(3);
    SmartInteger n2;
    EXPECT_EQ(n1.getValue(), 3);
    EXPECT_EQ(n2.getValue(), 0);

    // No need to implement custom copy assignment operator - this should just work
    n2 = 3;
    EXPECT_EQ(n2.getValue(), 3);

    // No need to implement custom copy constructor - this should just work
    SmartInteger n3(n2);
    EXPECT_EQ(n3.getValue(), 3);
}

#endif

#ifdef RunConstructorPrototypeTest

/**
 * @brief Test case to make sure the constructor and getValue() have the
 *        correct prototypes.
 */
TEST_F(A5Test, ConstructorPrototypeTest) {
    const SmartInteger n1(3);
    EXPECT_EQ(n1.getValue(), 3);
}

#endif

#ifdef RunPrintBasicTest

/**
 * @brief Test case to make sure the << operator behaves as desired.
 */
TEST_F(A5Test, PrintBasicTest) {
    SmartInteger n1(3);
    std::stringstream buff;

    buff << n1;
    buff << std::endl;
    MATCH_NEXT_LINE(buff, "3");
    MATCH_END(buff);
    clearBuff(buff);

    EXPECT_EQ(n1.getValue(), 3);
}

#endif

#ifdef RunPrintPrototypeTest

/**
 * @brief Test case to make sure the << operator has the correct prototype.
 */
TEST_F(A5Test, PrintPrototypeTest) {
    const SmartInteger n1(3);
    std::stringstream buff;
    // Convert to std::ostream, to make sure the prototype is correct
    std::ostream &stream = buff;

    stream << n1 << std::endl;
    MATCH_NEXT_LINE(buff, "3");
    MATCH_END(buff);
    clearBuff(buff);

    EXPECT_EQ(n1.getValue(), 3);
}

#endif

#ifdef RunComparisonBasicTest

/**
 * @brief Test case to make sure the <, >, <=, >=, ==, and != operators behave
 *        as desired.
 */
TEST_F(A5Test, ComparisonBasicTest) {
    SmartInteger n1(1);
    SmartInteger n2(2);
    SmartInteger n2Copy(2);
    SmartInteger n3(3);

    EXPECT_FALSE(n2 < n1);
    EXPECT_TRUE(n2 > n1);
    EXPECT_FALSE(n2 <= n1);
    EXPECT_TRUE(n2 >= n1);
    EXPECT_FALSE(n2 == n1);
    EXPECT_TRUE(n2 != n1);
    EXPECT_FALSE(n2 < n2Copy);
    EXPECT_FALSE(n2 > n2Copy);
    EXPECT_TRUE(n2 <= n2Copy);
    EXPECT_TRUE(n2 >= n2Copy);
    EXPECT_TRUE(n2 == n2Copy);
    EXPECT_FALSE(n2 != n2Copy);
    EXPECT_TRUE(n2 < n3);
    EXPECT_FALSE(n2 > n3);
    EXPECT_TRUE(n2 <= n3);
    EXPECT_FALSE(n2 >= n3);
    EXPECT_FALSE(n2 == n3);
    EXPECT_TRUE(n2 != n3);

    EXPECT_EQ(n1.getValue(), 1);
    EXPECT_EQ(n2.getValue(), 2);
    EXPECT_EQ(n2Copy.getValue(), 2);
    EXPECT_EQ(n3.getValue(), 3);
}

#endif

#ifdef RunComparisonPrototypeTest

/**
 * @brief Test case to make sure the <, >, <=, >=, ==, and != operators have
 *        the correct prototypes.
 */
TEST_F(A5Test, ComparisonPrototypeTest) {
    const SmartInteger n2(2);
    const SmartInteger n2Copy(2);

    EXPECT_FALSE(n2 < n2Copy);
    EXPECT_FALSE(n2 > n2Copy);
    EXPECT_TRUE(n2 <= n2Copy);
    EXPECT_TRUE(n2 >= n2Copy);
    EXPECT_TRUE(n2 == n2Copy);
    EXPECT_FALSE(n2 != n2Copy);

    // No need to have a prototype that takes an int parameter - this should just work
    EXPECT_FALSE(n2 < 2);
    EXPECT_FALSE(n2 > 2);
    EXPECT_TRUE(n2 <= 2);
    EXPECT_TRUE(n2 >= 2);
    EXPECT_TRUE(n2 == 2);
    EXPECT_FALSE(n2 != 2);

    EXPECT_EQ(n2.getValue(), 2);
    EXPECT_EQ(n2Copy.getValue(), 2);
}

#endif

#ifdef RunAdditionBasicTest

/**
 * @brief Test case to make sure the + and += operators behave as desired.
 */
TEST_F(A5Test, AdditionBasicTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() + std::declval<SmartInteger>(),
            SmartInteger
        ),
        "+ operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() += std::declval<SmartInteger>(),
            SmartInteger
        ),
        "+= operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(2);
    SmartInteger n2(-3);
    SmartInteger n3(std::numeric_limits<int>::max());
    SmartInteger n4(std::numeric_limits<int>::min());

    // Tests for + operator
    EXPECT_SMARTINTEGER_EQ(n1+n1, 4);
    EXPECT_SMARTINTEGER_EQ(n1+n2, -1);
    EXPECT_THROW(n1+n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n1+n4, 2+std::numeric_limits<int>::min());
    EXPECT_SMARTINTEGER_EQ(n2+n1, -1);
    EXPECT_SMARTINTEGER_EQ(n2+n2, -6);
    EXPECT_SMARTINTEGER_EQ(n2+n3, -3+std::numeric_limits<int>::max());
    EXPECT_THROW(n2+n4, std::exception);
    EXPECT_THROW(n3+n1, std::exception);
    EXPECT_SMARTINTEGER_EQ(n3+n2, std::numeric_limits<int>::max()-3);
    EXPECT_THROW(n3+n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n3+n4, std::numeric_limits<int>::max() + std::numeric_limits<int>::min());
    EXPECT_SMARTINTEGER_EQ(n4+n1, std::numeric_limits<int>::min()+2);
    EXPECT_THROW(n4+n2, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4+n3, std::numeric_limits<int>::min() + std::numeric_limits<int>::max());
    EXPECT_THROW(n4+n4, std::exception);

    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::max());
    EXPECT_SMARTINTEGER_EQ(n4, std::numeric_limits<int>::min());

    // Tests for += operator
    EXPECT_SMARTINTEGER_EQ(n1 += n2, -1);
    EXPECT_SMARTINTEGER_EQ(n1, -1);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    n1 = 2;

    EXPECT_THROW(n1 += n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::max());

    EXPECT_THROW(n2 += n4, std::exception);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n4, std::numeric_limits<int>::min());
}

#endif

#ifdef RunAdditionPrototypeTest

/**
 * @brief Test case to make sure the + and += operators have the correct
 *        prototype.
 */
TEST_F(A5Test, AdditionPrototypeTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() + std::declval<SmartInteger>(),
            SmartInteger
        ),
        "+ operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() += std::declval<SmartInteger>(),
            SmartInteger
        ),
        "+= operator must return SmartInteger by value, reference, const value, or const reference"
    );
    // This is a runtime check, so that if the prototype is wrong, then the student can still see
    // the outputs of the remaining assertions
    EXPECT_NOT_ASSIGNABLE(
        std::declval<SmartInteger>() + std::declval<SmartInteger>(),
        SmartInteger
    ) << "The line of code `(n1 + n2) = n3;` compiles, where n1, n2, and n3 are SmartIntegers";

    SmartInteger n1(2);
    const SmartInteger n2(-3);
    const SmartInteger n3(4);

    EXPECT_SMARTINTEGER_EQ((n1 + n2) + n3, 3);
    EXPECT_SMARTINTEGER_EQ((n2 + n1) + n3, 3);
    EXPECT_SMARTINTEGER_EQ(n1 + (n2 + n3), 3);
    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, 4);

    EXPECT_SMARTINTEGER_EQ((n1 += n2) += n3, 3);
    EXPECT_SMARTINTEGER_EQ(n1, 3);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, 4);
}

#endif

#ifdef RunSubtractionBasicTest

/**
 * @brief Test case to make sure the - and -= operators behave as desired.
 */
TEST_F(A5Test, SubtractionBasicTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() - std::declval<SmartInteger>(),
            SmartInteger
        ),
        "- operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() -= std::declval<SmartInteger>(),
            SmartInteger
        ),
        "-= operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(2);
    SmartInteger n2(-3);
    SmartInteger n3(std::numeric_limits<int>::max());
    SmartInteger n4(std::numeric_limits<int>::min());

    // Tests for - operator
    EXPECT_SMARTINTEGER_EQ(n1-n1, 0);
    EXPECT_SMARTINTEGER_EQ(n1-n2, 5);
    EXPECT_SMARTINTEGER_EQ(n1-n3, 2-std::numeric_limits<int>::max());
    EXPECT_THROW(n1-n4, std::exception);
    EXPECT_SMARTINTEGER_EQ(n2-n1, -5);
    EXPECT_SMARTINTEGER_EQ(n2-n2, 0);
    EXPECT_THROW(n2-n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n2-n4, -3-std::numeric_limits<int>::min());
    EXPECT_SMARTINTEGER_EQ(n3-n1, std::numeric_limits<int>::max()-2);
    EXPECT_THROW(n3-n2, std::exception);
    EXPECT_SMARTINTEGER_EQ(n3-n3, 0);
    EXPECT_THROW(n3-n4, std::exception);
    EXPECT_THROW(n4-n1, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4-n2, std::numeric_limits<int>::min()+3);
    EXPECT_THROW(n4-n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4-n4, 0);

    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::max());
    EXPECT_SMARTINTEGER_EQ(n4, std::numeric_limits<int>::min());

    // Tests for -= operator
    EXPECT_SMARTINTEGER_EQ(n1 -= n2, 5);
    EXPECT_SMARTINTEGER_EQ(n1, 5);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    n1 = 2;

    EXPECT_THROW(n1 -= n4, std::exception);
    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n4, std::numeric_limits<int>::min());

    EXPECT_THROW(n2 -= n3, std::exception);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::max());
}

#endif

#ifdef RunMultiplicationBasicTest

/**
 * @brief Test case to make sure the * and *= operators behave as desired.
 */
TEST_F(A5Test, MultiplicationBasicTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() * std::declval<SmartInteger>(),
            SmartInteger
        ),
        "* operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            std::declval<SmartInteger>() *= std::declval<SmartInteger>(),
            SmartInteger
        ),
        "*= operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(2);
    SmartInteger n2(-2);
    SmartInteger n3(3);
    SmartInteger n4(-3);
    SmartInteger n5(std::numeric_limits<int>::max() / 2 - 1);
    SmartInteger n6(std::numeric_limits<int>::min() / 2 + 1);

    // Tests for * operator
    EXPECT_SMARTINTEGER_EQ(n1*n1, 4);
    EXPECT_SMARTINTEGER_EQ(n1*n2, -4);
    EXPECT_SMARTINTEGER_EQ(n1*n3, 6);
    EXPECT_SMARTINTEGER_EQ(n1*n4, -6);
    EXPECT_SMARTINTEGER_EQ(n1*n5, 2 * (std::numeric_limits<int>::max() / 2 - 1));
    EXPECT_SMARTINTEGER_EQ(n1*n6, 2 * (std::numeric_limits<int>::min() / 2 + 1));
    EXPECT_SMARTINTEGER_EQ(n2*n1, -4);
    EXPECT_SMARTINTEGER_EQ(n2*n2, 4);
    EXPECT_SMARTINTEGER_EQ(n2*n3, -6);
    EXPECT_SMARTINTEGER_EQ(n2*n4, 6);
    EXPECT_SMARTINTEGER_EQ(n2*n5, -2 * (std::numeric_limits<int>::max() / 2 - 1));
    EXPECT_SMARTINTEGER_EQ(n2*n6, -2 * (std::numeric_limits<int>::min() / 2 + 1));
    EXPECT_SMARTINTEGER_EQ(n3*n1, 6);
    EXPECT_SMARTINTEGER_EQ(n3*n2, -6);
    EXPECT_SMARTINTEGER_EQ(n3*n3, 9);
    EXPECT_SMARTINTEGER_EQ(n3*n4, -9);
    EXPECT_THROW(n3*n5, std::exception);
    EXPECT_THROW(n3*n6, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4*n1, -6);
    EXPECT_SMARTINTEGER_EQ(n4*n2, 6);
    EXPECT_SMARTINTEGER_EQ(n4*n3, -9);
    EXPECT_SMARTINTEGER_EQ(n4*n4, 9);
    EXPECT_THROW(n4*n5, std::exception);
    EXPECT_THROW(n4*n6, std::exception);
    EXPECT_SMARTINTEGER_EQ(n5*n1, (std::numeric_limits<int>::max() / 2 - 1) * 2);
    EXPECT_SMARTINTEGER_EQ(n5*n2, (std::numeric_limits<int>::max() / 2 - 1) * -2);
    EXPECT_THROW(n5*n3, std::exception);
    EXPECT_THROW(n5*n4, std::exception);
    EXPECT_THROW(n5*n5, std::exception);
    EXPECT_THROW(n5*n6, std::exception);
    EXPECT_SMARTINTEGER_EQ(n6*n1, (std::numeric_limits<int>::min() / 2 + 1) * 2);
    EXPECT_SMARTINTEGER_EQ(n6*n2, (std::numeric_limits<int>::min() / 2 + 1) * -2);
    EXPECT_THROW(n6*n3, std::exception);
    EXPECT_THROW(n6*n4, std::exception);
    EXPECT_THROW(n6*n5, std::exception);
    EXPECT_THROW(n6*n6, std::exception);

    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n2, -2);
    EXPECT_SMARTINTEGER_EQ(n3, 3);
    EXPECT_SMARTINTEGER_EQ(n4, -3);
    EXPECT_SMARTINTEGER_EQ(n5, std::numeric_limits<int>::max() / 2 - 1);
    EXPECT_SMARTINTEGER_EQ(n6, std::numeric_limits<int>::min() / 2 + 1);

    // Tests for *= operator
    EXPECT_SMARTINTEGER_EQ(n1 *= n4, -6);
    EXPECT_SMARTINTEGER_EQ(n1, -6);
    EXPECT_SMARTINTEGER_EQ(n4, -3);
    n1 = 2;

    EXPECT_THROW(n3 *= n5, std::exception);
    EXPECT_SMARTINTEGER_EQ(n3, 3);
    EXPECT_SMARTINTEGER_EQ(n5, std::numeric_limits<int>::max() / 2 - 1);

    EXPECT_THROW(n3 *= n6, std::exception);
    EXPECT_SMARTINTEGER_EQ(n3, 3);
    EXPECT_SMARTINTEGER_EQ(n6, std::numeric_limits<int>::min() / 2 + 1);

    EXPECT_THROW(n4 *= n5, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4, -3);
    EXPECT_SMARTINTEGER_EQ(n5, std::numeric_limits<int>::max() / 2 - 1);

    EXPECT_THROW(n4 *= n6, std::exception);
    EXPECT_SMARTINTEGER_EQ(n4, -3);
    EXPECT_SMARTINTEGER_EQ(n6, std::numeric_limits<int>::min() / 2 + 1);
}

#endif

#ifdef RunNegationBasicTest

/**
 * @brief Test case to make sure the unary - operator behaves as desired.
 */
TEST_F(A5Test, NegationBasicTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            -std::declval<SmartInteger>(),
            SmartInteger
        ),
        "- operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(2);
    SmartInteger n2(-3);
    SmartInteger n3(std::numeric_limits<int>::max());
    SmartInteger n4(std::numeric_limits<int>::min());

    EXPECT_SMARTINTEGER_EQ(-n1, -2);
    EXPECT_SMARTINTEGER_EQ(-n2, 3);
    EXPECT_SMARTINTEGER_EQ(-n3, -std::numeric_limits<int>::max());
    EXPECT_THROW(-n4, std::exception);

    EXPECT_SMARTINTEGER_EQ(n1, 2);
    EXPECT_SMARTINTEGER_EQ(n2, -3);
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::max());
    EXPECT_SMARTINTEGER_EQ(n4, std::numeric_limits<int>::min());
}

#endif

#ifdef RunPreIncrementBasicTest

/**
 * @brief Test case to make sure the prefix ++ and -- operators behave as
 *        desired.
 */
TEST_F(A5Test, PreIncrementBasicTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            ++std::declval<SmartInteger>(),
            SmartInteger
        ),
        "++ operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            --std::declval<SmartInteger>(),
            SmartInteger
        ),
        "-- operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(3);
    SmartInteger n2(std::numeric_limits<int>::max());
    SmartInteger n3(std::numeric_limits<int>::min());

    EXPECT_SMARTINTEGER_EQ(++n1, 4);
    EXPECT_SMARTINTEGER_EQ(n1, 4);
    EXPECT_SMARTINTEGER_EQ(--n1, 3);
    EXPECT_SMARTINTEGER_EQ(n1, 3);
    EXPECT_SMARTINTEGER_EQ(--n2, std::numeric_limits<int>::max() - 1);
    EXPECT_SMARTINTEGER_EQ(++n2, std::numeric_limits<int>::max());
    EXPECT_THROW(++n2, std::exception);
    EXPECT_SMARTINTEGER_EQ(++n3, std::numeric_limits<int>::min() + 1);
    EXPECT_SMARTINTEGER_EQ(--n3, std::numeric_limits<int>::min());
    EXPECT_THROW(--n3, std::exception);

    EXPECT_SMARTINTEGER_EQ(n1, 3);
    EXPECT_SMARTINTEGER_EQ(n2, std::numeric_limits<int>::max());
    EXPECT_SMARTINTEGER_EQ(n3, std::numeric_limits<int>::min());
}

#endif

#ifdef RunPreIncrementPrototypeTest

/**
 * @brief Test case to make sure the prefix ++ and -- operators have the
 *        correct prototypes.
 */
TEST_F(A5Test, PreIncrementPrototypeTest) {
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            ++std::declval<SmartInteger>(),
            SmartInteger
        ),
        "++ operator must return SmartInteger by value, reference, const value, or const reference"
    );
    static_assert(
        HAS_STRIPPED_RETURN_TYPE(
            --std::declval<SmartInteger>(),
            SmartInteger
        ),
        "-- operator must return SmartInteger by value, reference, const value, or const reference"
    );

    SmartInteger n1(3);

    EXPECT_SMARTINTEGER_EQ(++(++n1), 5);
    EXPECT_SMARTINTEGER_EQ(n1, 5);
    EXPECT_SMARTINTEGER_EQ(--(--n1), 3);
    EXPECT_SMARTINTEGER_EQ(n1, 3);
}

#endif

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
