///////////////////////////////////////////////////////////////////////////////
// File Name:      SmartInteger.cpp
//
// Author:         Kevin Mui
// CS email:       mui@cs.wisc.edu
//
// Description:    Methods to perform some processing on smart integers.
///////////////////////////////////////////////////////////////////////////////
#include "SmartInteger.hpp"

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <sstream> 
#include <exception>

SmartInteger::SmartInteger() {
    // default to 0
    this->num = 0;
}

SmartInteger::SmartInteger(const int num) {
    // initialize to num
    this->num = num;
}

int SmartInteger::getValue() const {
    // return as int
    return this->num;
}

std::ostream& operator<<(std::ostream& os, const SmartInteger& rhs) {
    // print out to out stream
    os << rhs.getValue();
    return os;
}

const bool SmartInteger::operator<(const SmartInteger rhs) const {
    // compare as int for < 
    return this->num < rhs.getValue();
}

const bool  SmartInteger::operator>(const SmartInteger rhs) const {
    // compare as int for >
    return this->num > rhs.getValue();
}

const bool SmartInteger::operator<=(const SmartInteger rhs) const {
    // compare as int for <=
    return this->num <= rhs.getValue();
}

const bool SmartInteger::operator>=(const SmartInteger rhs) const {
    // compare as int for >=
    return this->num >= rhs.getValue();
}

const bool SmartInteger::operator==(const SmartInteger rhs) const {
    // compare as int for ==
    return this->num == rhs.getValue();
}

const bool SmartInteger::operator!=(const SmartInteger rhs) const {
    // compare as int for != 
    return this->num != rhs.getValue();
}

const SmartInteger SmartInteger::operator+(const SmartInteger rhs) const{
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

    // check whether lhs and rhs positive or negative
     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.getValue() > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.getValue() < 0;

    // max integer overflow if adding two positive integers that end up greater than maxInt
    // (comparison expression modified to prevent overflow)
    if (lhsPos && rhsPos && (maxInt - this->num < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    // min integer overlfow if adding two negative integers that end up less than minInt
    // (comparison expression modified to prevent overflow) 
    else if (lhsNeg && rhsNeg && (this->num == minInt || rhs.getValue() == minInt || 
                minInt - this->num > rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Min Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    // no overflow detected so it's safe to return the sum
    SmartInteger sum;
    sum.num = this->num + rhs.getValue();
    return sum;
}

const SmartInteger SmartInteger::operator-(const SmartInteger rhs) const {
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.getValue() > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.getValue() < 0;

    // max integer overflow if subtracting one negative integer FROM a positive integer
    // that end up greater than maxInt (comparison expression modified to prevent overflow)
    if (lhsPos && rhsNeg && (rhs.getValue() == minInt || maxInt - this->num < -rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    // min integer overlfow if stracting one positive integer FROM a negative integer 
    // that end up less than minInt (comparison expression modified to prevent overflow)
    else if (lhsNeg && rhsPos && (this->num == minInt || minInt - rhs.getValue() < -this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    // no overflow detected so it's safe to return the difference
    SmartInteger diff;
    diff.num = this->num - rhs.getValue();
    return diff;
}

const SmartInteger SmartInteger::operator*(const SmartInteger rhs) const {
    // product is 0 if either of the two integers are 0 
    // (helps prevent divide by zero when doing other overflow checking)
    if (this->num == 0 || rhs.getValue() == 0)
        return SmartInteger(0);
    
    int maxInt = std::numeric_limits<int>::max();
    int minInt = std::numeric_limits<int>::min();

    bool lhsPos = this->num > 0;
    bool rhsPos = rhs.getValue() > 0;
    bool lhsNeg = this->num < 0;
    bool rhsNeg = rhs.getValue() < 0;

    /////////////////////////////////////////////////////
    // check for all cases of signs for both integers //
    ///////////////////////////////////////////////////

    // check for overflow with both positive integers
    // (comparison expression modified to prevent overflow) 
    if (lhsPos && rhsPos && (maxInt/this->num < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    // check for overflow with both negative values
    // (comparison expression modified to prevent overflow) 
    else if (lhsNeg && rhsNeg && (this->num == minInt || rhs.getValue() == minInt || 
                    maxInt/(-this->num) < -rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    // check for overflow with lhs is positive and rhs is negative
    // (comparison expression modified to prevent overflow) 
    else if (lhsPos && rhsNeg && (minInt/(rhs.getValue()) < this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    // check for overflow with lhs is negative and rhs is positive
    // (comparison expression modified to prevent overflow) 
    else if (lhsNeg && rhsPos && (minInt/(this->num) < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    // no overflow detected so it's safe to return the product
    SmartInteger product;
    product.num = this->num * rhs.getValue();
    return product;
};

SmartInteger& SmartInteger::operator+=(const SmartInteger rhs) {
    // update this and return sum
    *this = *this + rhs;
    return *this;
};

SmartInteger& SmartInteger::operator-=(const SmartInteger rhs) {
    // update this and return difference
    *this = *this - rhs;
    return *this;
}

SmartInteger& SmartInteger::operator*=(const SmartInteger rhs) {
    // update this and return product
    *this = *this * rhs;
    return *this;
}

SmartInteger& SmartInteger::operator++() {
    // update this and return sum
    *this = *this + SmartInteger(1);
    return *this;
}

SmartInteger& SmartInteger::operator--() {
    // update this and return difference
    *this = *this - SmartInteger(1);
    return *this;
}