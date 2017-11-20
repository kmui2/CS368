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
#include <cmath> 
#include <limits>
#include <sstream> 
#include <exception>

SmartInteger::SmartInteger() {
    this->num = 0;
}

SmartInteger::SmartInteger(const int num) {
    this->num = num;
}

const int SmartInteger::getValue() const {
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
    const int maxInt = std::numeric_limits<int>::max();
    const int minInt = std::numeric_limits<int>::min();

    const bool lhsPos = this->num > 0;
    const bool rhsPos = rhs.num > 0;
    const bool lhsNeg = this->num < 0;
    const bool rhsNeg = rhs.num < 0;

    if (lhsPos && rhsPos && (maxInt - this->num < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (minInt - this->num > rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger sum;
    sum.num = this->num + rhs.num;
    return sum;
}

const SmartInteger SmartInteger::operator-(const SmartInteger rhs) {
    const int maxInt = std::numeric_limits<int>::max();
    const int minInt = std::numeric_limits<int>::min();

    const bool lhsPos = this->num > 0;
    const bool rhsPos = rhs.num > 0;
    const bool lhsNeg = this->num < 0;
    const bool rhsNeg = rhs.num < 0;

    if (lhsPos && rhsNeg && (maxInt - this->num < -rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt - rhs.num < -this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger diff;
    diff.num = this->num - rhs.num;
    return diff;
}

const SmartInteger SmartInteger::operator*(const SmartInteger rhs) {
    if (this->num == 0 || rhs.num == 0) {
        return SmartInteger(0);
    }
    const int maxInt = std::numeric_limits<int>::max();
    const int minInt = std::numeric_limits<int>::min();

    const bool lhsPos = this->num > 0;
    const bool rhsPos = rhs.num > 0;
    const bool lhsNeg = this->num < 0;
    const bool rhsNeg = rhs.num < 0;

    if (lhsPos && rhsPos && (maxInt/this->num < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (maxInt/(-this->num) < -rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsPos && rhsNeg && (minInt/(rhsNeg) < this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt/(this->num) < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger product;
    product.num = this->num * rhs.num;
    return product;
};

const SmartInteger SmartInteger::operator+=(const SmartInteger rhs) {
    *this = *this + rhs;
    return *this;
};

const SmartInteger SmartInteger::operator-=(const SmartInteger rhs) {
    *this = *this - rhs;
    return *this;
}

const SmartInteger SmartInteger::operator*=(const SmartInteger rhs) {
    *this = *this * rhs;
    return *this;
}

const SmartInteger SmartInteger::operator++() {
    *this = *this + SmartInteger(1);
    return *this;
}

const SmartInteger SmartInteger::operator--() {
    *this = *this - SmartInteger(1);
    return *this;
}