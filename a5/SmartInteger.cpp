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

std::ostream& operator<<(std::ostream& os, const SmartInteger& rhs) {
    os << rhs.getValue();
    return os;
}

bool SmartInteger::operator<( SmartInteger rhs) const {
    return this->num < rhs.getValue();
}

bool  SmartInteger::operator>( SmartInteger rhs) const {
    return this->num > rhs.getValue();
}

bool SmartInteger::operator<=( SmartInteger rhs) const {
    return this->num <= rhs.getValue();
}

bool SmartInteger::operator>=( SmartInteger rhs) const {
    return this->num >= rhs.getValue();
}

bool SmartInteger::operator==( SmartInteger rhs) const {
    return this->num == rhs.getValue();
}

bool SmartInteger::operator!=( SmartInteger rhs) const {
    return this->num != rhs.getValue();
}

SmartInteger SmartInteger::operator+( SmartInteger rhs) const{
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.getValue() > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.getValue() < 0;

    if (lhsPos && rhsPos && (maxInt - this->num < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (minInt - this->num > rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Min Integer addition overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger sum;
    sum.num = this->num + rhs.getValue();
    return sum;
}

SmartInteger SmartInteger::operator-( SmartInteger rhs) const {
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.getValue() > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.getValue() < 0;

    if (lhsPos && rhsNeg && (maxInt - this->num < -rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt - rhs.getValue() < -this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer subtraction overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger diff;
    diff.num = this->num - rhs.getValue();
    return diff;
}

SmartInteger SmartInteger::operator*( SmartInteger rhs) const {
    if (this->num == 0 || rhs.getValue() == 0) {
        return SmartInteger(0);
    }
     int maxInt = std::numeric_limits<int>::max();
     int minInt = std::numeric_limits<int>::min();

     bool lhsPos = this->num > 0;
     bool rhsPos = rhs.getValue() > 0;
     bool lhsNeg = this->num < 0;
     bool rhsNeg = rhs.getValue() < 0;

    if (lhsPos && rhsPos && (maxInt/this->num < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (maxInt/(-this->num) < -rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsPos && rhsNeg && (minInt/(rhsNeg) < this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt/(this->num) < rhs.getValue())) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::runtime_error(errMsg.str().c_str());
    }

    SmartInteger product;
    product.num = this->num * rhs.getValue();
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