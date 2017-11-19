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
        errMsg << "Max Integer addition overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (minInt - this->num > rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer addition overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }

    SmartInteger sum;
    sum.num = this->num + rhs.num;
    return sum;
}

const SmartInteger SmartInteger::operator-(const SmartInteger rhs) {
    int maxInt = std::numeric_limits<int>::max();
    int minInt = std::numeric_limits<int>::min();

    bool lhsPos = this->num > 0;
    bool rhsPos = rhs.num > 0;
    bool lhsNeg = this->num < 0;
    bool rhsNeg = rhs.num < 0;

    if (lhsPos && rhsNeg && (maxInt - this->num < -rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer subtraction overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt - rhs.num < -this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer subtraction overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }

    SmartInteger diff;
    diff.num = this->num - rhs.num;
    return diff;
}

const SmartInteger operator*(const SmartInteger rhs) {
    if (this->num == 0 || rhs.num == 0) {
        return new SmartInteger(0);
    }
    int maxInt = std::numeric_limits<int>::max();
    int minInt = std::numeric_limits<int>::min();

    if (lhsPos && rhsPos && (maxInt/this->num < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsNeg && (maxInt/(-this->num) < -rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Max Integer multiplication overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsPos && rhsNeg && (minInt/(rhsNeg) < this->num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }
    else if (lhsNeg && rhsPos && (minInt/(this->num) < rhs.num)) {
        std::stringstream errMsg;
        errMsg << "Min Integer multiplication overflow occurred";
        throw std::exception(errMsg.str().c_str());
    }

    SmartInteger product;
    product.num = this->num * rhs.num;
    return product;
};

const SmartInteger operator+=(const SmartInteger rhs) {
    *this = *this + rhs;
    return *this;
};

const SmartInteger operator-=(const SmartInteger rhs) {
    *this = *this - rhs;
    return *this;
}

const SmartInteger operator*=(const SmartInteger rhs) {
    *this = *this * rhs;
    return *this;
}

const SmartInteger ++operator() {
    SmartInteger one = new SmartInteger(1);
    *this = *this + one;
    return *this;
}

const SmartInteger --operator() {
    SmartInteger one = new SmartInteger(1);
    *this = *this - one;
    return *this;
}