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

SmartInteger::SmartInteger() {
    this->num = 0;
}

SmartInteger::SmartInteger(const int num) {
    this->num = num;
}

const int SmartInteger::getValue() {
    return this->num;
}

std::ostream& SmartInteger::operator<<(std::ostream& os) {
    os << this->num;
    return os;
}

const bool SmartInteger::operator<(const SmartInteger rhs) {
    return this->num < rhs.num;
}

const bool  SmartInteger::operator>(const SmartInteger rhs) {
    return this->num > rhs.num;
}

const bool SmartInteger::operator<=(const SmartInteger rhs) {
    return this->num <= rhs.num;
}

const bool SmartInteger::operator>=(const SmartInteger rhs) {
    return this->num >= rhs.num;
}

const bool SmartInteger::operator==(const SmartInteger rhs) {
    return this->num == rhs.num;
}

const bool SmartInteger::operator!=(const SmartInteger rhs) {
    return this->num != rhs.num;
}

const SmartInteger SmartInteger::operator+(const SmartInteger rhs) {
    int maxInt = std::numeric_limits<int>::max();
    int minInt = std::numeric_limits<int>::min();

    bool lhsPos = this->num > 0;
    bool rhsPos = rhs.num > 0;
    bool lhsNeg = this->num < 0;
    bool rhsNeg = rhs.num < 0;

    if (lhsPos && rhsPos && (maxInt - this->num < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (minInt - this->num > rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    
    int sum = this->num + rhs.num;
    SmartInteger sumSMInt;
    sum.num = this->num + rhs.num;
    return sum;
}