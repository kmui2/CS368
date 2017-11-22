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

SmartInteger::SmartInteger(int num) {
    this->num = num;
}

int SmartInteger::getValue() const {
    return this->num;
}

std::ostream& SmartInteger::operator<<(std::ostream& os, SmartInteger rhs) const {
    os << rhs.num;
    return os;
}

bool SmartInteger::operator<( SmartInteger rhs) const {
    return this->num < rhs.num;
}

bool  SmartInteger::operator>( SmartInteger rhs) const {
    return this->num > rhs.num;
}

bool SmartInteger::operator<=( SmartInteger rhs) const {
    return this->num <= rhs.num;
}

bool SmartInteger::operator>=( SmartInteger rhs) const {
    return this->num >= rhs.num;
}

bool SmartInteger::operator==( SmartInteger rhs) const {
    return this->num == rhs.num;
}

bool SmartInteger::operator!=( SmartInteger rhs) const {
    return this->num != rhs.num;
}

SmartInteger SmartInteger::operator+( SmartInteger rhs) const{
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.num > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.num < 0;

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

SmartInteger SmartInteger::operator-( SmartInteger rhs) const {
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.num > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.num < 0;

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

SmartInteger SmartInteger::operator*( SmartInteger rhs) const {
    if (this->num == 0 || rhs.num == 0) {
        return SmartInteger(0);
    }
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.num > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.num < 0;

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

SmartInteger SmartInteger::operator+=( SmartInteger rhs) {
    *this = *this + rhs;
    return *this;
};

SmartInteger SmartInteger::operator-=( SmartInteger rhs) {
    *this = *this - rhs;
    return *this;
}

SmartInteger SmartInteger::operator*=( SmartInteger rhs) {
    *this = *this * rhs;
    return *this;
}

SmartInteger SmartInteger::operator++() {
    *this = *this + SmartInteger(1);
    return *this;
}

SmartInteger SmartInteger::operator--() {
    *this = *this - SmartInteger(1);
    return *this;
}