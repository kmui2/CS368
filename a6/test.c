///////////////////////////////////////////////////////////////////////////////
// File Name:      test.c
//
// Author:         Varun Naik
// CS email:       vnaik@cs.wisc.edu
//
// Description:    Unit tests for a6. As a reminder, even if you pass all of
//                 these tests, you are not yet guaranteed 100/100 on the
//                 assignment. But if you do not pass these tests, you will
//                 probably receive a very low score on the autograder.
//
// Sources:        Google Test, cppreference.com, Linux man pages
//
// URL(s) of sources:
//                 https://github.com/google/googletest
//                 http://en.cppreference.com/w/
//                 https://linux.die.net/
///////////////////////////////////////////////////////////////////////////////

#include "Vector.hpp"

#include "gtest/gtest.h"

#include <stdexcept>
#include <sys/resource.h>
#include <type_traits>

/**
 * @brief Compile-time checks for the Vector class. This function is never
 *        called, but it should compile without any errors.
 */
void compilerChecks() {
    // Iterator definitions
    static_assert(
        std::is_same<Vector<int>::iterator, int *>::value,
        "Vector<int>::iterator is not aliased to int *"
    );
    static_assert(
        std::is_same<Vector<int>::constIterator, const int *>::value,
        "Vector<int>::constIterator is not aliased to const int *"
    );
    static_assert(
        std::is_same<Vector<double>::iterator, double *>::value,
        "Vector<double>::iterator is not aliased to double *"
    );
    static_assert(
        std::is_same<Vector<double>::constIterator, const double *>::value,
        "Vector<double>::constIterator is not aliased to const double *"
    );

    // Check constructors
    Vector<int> vInt;
    const Vector<int> &vIntRef = vInt;
    Vector<double> vDouble;
    const Vector<double> &vDoubleRef = vDouble;
    static_assert(
        std::is_copy_constructible<Vector<int>>::value,
        "Vector<int> is not copy constructible"
    );
    static_assert(
        std::is_copy_constructible<Vector<double>>::value,
        "Vector<double> is not copy constructible"
    );

    // Check return types
    static_assert(
        std::is_same<Vector<int> &, decltype(vInt.operator=(vIntRef))>::value,
        "Vector<int>::operator= prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double> &, decltype(vDouble.operator=(vDoubleRef))>::value,
        "Vector<double>::operator= prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<int>::iterator, decltype(vInt.begin())>::value,
        "Vector<int>::begin() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double>::iterator, decltype(vDouble.begin())>::value,
        "Vector<double>::begin() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<int>::constIterator, decltype(vIntRef.begin())>::value,
        "Vector<int>::begin() const prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double>::constIterator, decltype(vDoubleRef.begin())>::value,
        "Vector<double>::begin() const prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<int>::iterator, decltype(vInt.end())>::value,
        "Vector<int>::end() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double>::iterator, decltype(vDouble.end())>::value,
        "Vector<double>::end() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<int>::constIterator, decltype(vIntRef.end())>::value,
        "Vector<int>::end() const prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double>::constIterator, decltype(vDoubleRef.end())>::value,
        "Vector<double>::end() const prototype is incorrect"
    );
    static_assert(
        std::is_same<std::size_t, decltype(vIntRef.capacity())>::value,
        "Vector<int>::capacity() prototype is incorrect"
    );
    static_assert(
        std::is_same<std::size_t, decltype(vIntRef.size())>::value,
        "Vector<int>::size() prototype is incorrect"
    );
    static_assert(
        std::is_same<void, decltype(vInt.pushBack(0))>::value,
        "Vector<int>::pushBack() prototype is incorrect"
    );
    static_assert(
        std::is_same<void, decltype(vInt.popBack())>::value,
        "Vector<int>::popBack() prototype is incorrect"
    );
    static_assert(
        std::is_same<void, decltype(vInt.reserve(0))>::value,
        "Vector<int>::reserve() prototype is incorrect"
    );
    static_assert(
        std::is_same<int &, decltype(vInt[0])>::value,
        "Vector<int>::operator[] prototype is incorrect"
    );
    static_assert(
        std::is_same<double &, decltype(vDouble[0])>::value,
        "Vector<double>::operator[] prototype is incorrect"
    );
    static_assert(
        std::is_same<const int &, decltype(vIntRef[0])>::value,
        "Vector<int>::operator[] const prototype is incorrect"
    );
    static_assert(
        std::is_same<const double &, decltype(vDoubleRef[0])>::value,
        "Vector<double>::operator[] const prototype is incorrect"
    );
    static_assert(
        std::is_same<int &, decltype(vInt.at(0))>::value,
        "Vector<int>::at() prototype is incorrect"
    );
    static_assert(
        std::is_same<double &, decltype(vDouble.at(0))>::value,
        "Vector<double>::at() prototype is incorrect"
    );
    static_assert(
        std::is_same<const int &, decltype(vIntRef.at(0))>::value,
        "Vector<int>::at() const prototype is incorrect"
    );
    static_assert(
        std::is_same<const double &, decltype(vDoubleRef.at(0))>::value,
        "Vector<double>::at() const prototype is incorrect"
    );
    static_assert(
        std::is_same<bool, decltype(vIntRef.empty())>::value,
        "Vector<int>::empty() prototype is incorrect"
    );
    static_assert(
        std::is_same<void, decltype(vInt.clear())>::value,
        "Vector<int>::clear() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<int>::iterator, decltype(vInt.erase(vInt.begin()))>::value,
        "Vector<int>::erase() prototype is incorrect"
    );
    static_assert(
        std::is_same<Vector<double>::iterator, decltype(vDouble.erase(vDouble.begin()))>::value,
        "Vector<double>::erase() prototype is incorrect"
    );
}

/**
 * @brief A test fixture class for all a6 tests.
 *
 * Normally, the implementation of each method would be in a separate file. We
 * put everything in here to be concise - we only want one test file with C++
 * code.
 */
class A6Test : public ::testing::Test {
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

#ifdef RunBasicTest

/**
 * @brief Test case that checks basic behavior for capacity(), size(), empty(),
 *        pushBack(), operator[], and at().
 */
TEST_F(A6Test, BasicTest) {
    Vector<int> v1;
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    v1.pushBack(1);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);

    v1.pushBack(2);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.empty(), false);

    v1.pushBack(3);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.empty(), false);

    v1.pushBack(4);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.empty(), false);

    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);

    EXPECT_EQ(v1.at(0), 1);
    EXPECT_EQ(v1.at(1), 2);
    EXPECT_EQ(v1.at(2), 3);
    EXPECT_EQ(v1.at(3), 4);
    EXPECT_EQ(v1.at(4), 5);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
}

#endif

#ifdef RunPushTest

/**
 * @brief Test case for pushBack().
 *
 * If pushBack() is called and a resize does not occur, then the begin iterator
 * should be unchanged. All elements should be contiguous in memory.
 */
TEST_F(A6Test, PushTest) {
    Vector<int> v1;
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);
    Vector<int>::iterator begin = v1.begin();

    v1.pushBack(1);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin(), &v1[0]);

    v1.pushBack(2);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin(), &v1[0]);
    EXPECT_EQ(v1.begin() + 1, &v1[1]);

    v1.pushBack(3);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin(), &v1[0]);
    EXPECT_EQ(v1.begin() + 1, &v1[1]);
    EXPECT_EQ(v1.begin() + 2, &v1[2]);

    v1.pushBack(4);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin(), &v1[0]);
    EXPECT_EQ(v1.begin() + 1, &v1[1]);
    EXPECT_EQ(v1.begin() + 2, &v1[2]);
    EXPECT_EQ(v1.begin() + 3, &v1[3]);
}

#endif

#ifdef RunPopTest

/**
 * @brief Test case for popBack().
 */
TEST_F(A6Test, PopTest) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.empty(), false);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.empty(), false);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.empty(), false);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    v1.popBack();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    // Make sure v1 can still be used normally
    v1.pushBack(10);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);
}

#endif

#ifdef RunReserveTest

/**
 * @brief Test case for reserve().
 */
TEST_F(A6Test, ReserveTest) {
    Vector<int> v1;
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    // Reserve less space
    v1.reserve(2);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);

    // Reserve more space
    v1.reserve(16);
    EXPECT_EQ(v1.capacity(), 16);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);
}

#endif

#ifdef RunClearTest

/**
 * @brief Test case for clear().
 */
TEST_F(A6Test, ClearTest) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    v1.clear();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    v1.clear();
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);

    // Make sure v1 can still be used normally
    v1.pushBack(10);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);
}

#endif

#ifdef RunIteratorTest

/**
 * @brief Test case for begin(), end(), and erase().
 */
TEST_F(A6Test, IteratorTest) {
    // It is okay to create a const reference to an object, and modify the object
    // through another name. See: https://stackoverflow.com/questions/13918283/
    Vector<int> v1;
    Vector<int>::iterator it;
    const Vector<int> &v1Ref = v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin() + 5, v1.end());
    EXPECT_EQ(v1Ref.begin() + 5, v1Ref.end());
    Vector<int>::iterator begin = v1.begin();

    it = v1.erase(v1.begin() + 1);
    EXPECT_EQ(it, v1.begin() + 1);
    EXPECT_EQ(it, v1Ref.begin() + 1);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin() + 4, v1.end());
    EXPECT_EQ(v1Ref.begin() + 4, v1Ref.end());
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 3);
    EXPECT_EQ(v1[2], 4);
    EXPECT_EQ(v1[3], 5);

    it = v1.erase(v1.begin() + 2);
    EXPECT_EQ(it, v1.begin() + 2);
    EXPECT_EQ(it, v1Ref.begin() + 2);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin() + 3, v1.end());
    EXPECT_EQ(v1Ref.begin() + 3, v1Ref.end());
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 3);
    EXPECT_EQ(v1[2], 5);

    it = v1.erase(v1.begin());
    EXPECT_EQ(it, v1.begin());
    EXPECT_EQ(it, v1Ref.begin());
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin() + 2, v1.end());
    EXPECT_EQ(v1Ref.begin() + 2, v1Ref.end());
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[1], 5);

    it = v1.erase(v1.begin() + 1);
    EXPECT_EQ(it, v1.begin() + 1);
    EXPECT_EQ(it, v1Ref.begin() + 1);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin() + 1, v1.end());
    EXPECT_EQ(v1Ref.begin() + 1, v1Ref.end());
    EXPECT_EQ(v1[0], 3);

    it = v1.erase(v1.begin());
    EXPECT_EQ(it, v1.begin());
    EXPECT_EQ(it, v1Ref.begin());
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.empty(), true);
    EXPECT_EQ(v1.begin(), begin);
    EXPECT_EQ(v1.begin(), v1.end());
    EXPECT_EQ(v1Ref.begin(), v1Ref.end());
}

#endif

#ifdef RunBracketAtTest

/**
 * @brief Test case for operator[] and at().
 */
TEST_F(A6Test, BracketAtTest) {
    Vector<int> v1;
    const Vector<int> &v1Ref = v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    // Check both non-const and const overload of each operator
    v1[0] = 10;
    EXPECT_EQ(v1[0], 10);
    EXPECT_EQ(v1Ref[0], 10);
    EXPECT_EQ(v1.at(0), 10);
    EXPECT_EQ(v1Ref.at(0), 10);

    v1.at(0) = 20;
    EXPECT_EQ(v1[0], 20);
    EXPECT_EQ(v1Ref[0], 20);
    EXPECT_EQ(v1.at(0), 20);
    EXPECT_EQ(v1Ref.at(0), 20);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    int value;
    EXPECT_NO_THROW({
        value = v1Ref[5];
    });
    EXPECT_NO_THROW({
        v1[5] = 0;
    });

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);

    EXPECT_THROW({
        value = v1Ref.at(5);
    }, std::out_of_range);
    EXPECT_THROW({
        v1.at(5) = 0;
    }, std::out_of_range);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
}

#endif

#ifdef RunCopyConstructorTest

/**
 * @brief Test case for the copy constructor.
 */
TEST_F(A6Test, CopyConstructorTest) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);

    Vector<int> v2(v1);
    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v2[3], 4);
    EXPECT_EQ(v2[4], 5);

    v1.pushBack(6);
    v2.pushBack(7);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 6);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[5], 6);

    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 6);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[5], 7);
}

#endif

#ifdef RunCopyAssignmentTest

/**
 * @brief Test case for the copy assignment operator.
 */
TEST_F(A6Test, CopyAssignmentTest) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);

    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v2[3], 4);
    EXPECT_EQ(v2[4], 5);

    v1.pushBack(6);
    v2.pushBack(7);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 6);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[5], 6);

    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 6);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[5], 7);
}

#endif

#ifdef RunSelfAssignmentTest

namespace SelfAssignmentTestNamespace {
    bool replaceWithZeros = false;
};

/**
 * @brief Custom delete operator for SelfAssignmentTest. Replaces the first int
 *        in the allocated area with 0 if necessary. The operator causes a
 *        memory leak; the memory is not deallocated. This behavior should be
 *        fine, because the test case should not perform very many memory
 *        allocations/deallocations.
 *
 * @param ptr A pointer to the memory location
 */
void operator delete(void *ptr) throw() {
    if (SelfAssignmentTestNamespace::replaceWithZeros) {
        int *intPtr = (int *)ptr;
        *intPtr = 0;
    }
}

/**
 * @brief Custom delete[] operator for SelfAssignmentTest.
 *
 * See the delete operator for more information.
 *
 * @param ptr A pointer to the memory location
 */
void operator delete[](void *ptr) throw() {
    if (SelfAssignmentTestNamespace::replaceWithZeros) {
        int *intPtr = (int *)ptr;
        *intPtr = 0;
    }
}

/**
 * @brief Test case for self assignment using the copy assignment operator.
 */
TEST_F(A6Test, SelfAssignmentTest) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);
    v1.pushBack(3);
    v1.pushBack(4);
    v1.pushBack(5);
    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);

    // Make sure normal copy assignment works
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v2[3], 4);
    EXPECT_EQ(v2[4], 5);

    v1.pushBack(6);
    v2.pushBack(7);

    EXPECT_EQ(v1.capacity(), 8);
    EXPECT_EQ(v1.size(), 6);
    EXPECT_EQ(v1.empty(), false);
    EXPECT_EQ(v1[5], 6);

    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 6);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[5], 7);

    // Perform self assignment
    SelfAssignmentTestNamespace::replaceWithZeros = true;
    v2 = v2;
    SelfAssignmentTestNamespace::replaceWithZeros = false;
    EXPECT_EQ(v2.capacity(), 8);
    EXPECT_EQ(v2.size(), 6);
    EXPECT_EQ(v2.empty(), false);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v2[3], 4);
    EXPECT_EQ(v2[4], 5);
    EXPECT_EQ(v2[5], 7);
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
    // Limit size of virtual memory to 2^25 bytes
    // See: https://linux.die.net/man/2/setrlimit
    struct rlimit lim;
    lim.rlim_cur = 33554432;
    lim.rlim_max = 33554432;
    int status = setrlimit(RLIMIT_AS, &lim);
    if (status == -1) {
        return 1;
    }

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
