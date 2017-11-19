///////////////////////////////////////////////////////////////////////////////
// File Name:      SmartInteger.hpp
//
// Author:         Kevin Mui
// CS email:       mui@cs.wisc.edu
//
// Description:    Methods to perform some processing on smart integers.
///////////////////////////////////////////////////////////////////////////////

#ifndef A5_SMARTINTEGER_HPP
#define A5_SMARTINTEGER_HPP

#include <iostream>

class SmartInteger {
    private:
        int num;
    
    public:
        /**
         * @brief a default constructor for SmartInteger that sets 
         * the integer value to a default value of 0.
         * */
        SmartInteger();

        /**
         * @brief a parameterized constructor for SmartInteger that sets the 
         * starting integer value to num.
         * */
        SmartInteger(int num);

        /**
         * @brief This function is a simple getter that returns the integer value of the 
         * SmartInteger.
         * 
         * @return the SmartInteger as an int
         * */
        int getValue();

        /**
         * @brief an overloaded operator << for ostream and SmartInteger. This should 
         * display the integer value of the SmartInteger as if it were calling getValue().
         * 
         * @return the out stream
         * */
        std::ostream& operator<<(std::ostream& os, const Complex& rhs);

        /**
         * @brief an overloaded operator < that returns whether or not the value of the left hand s
         * ide SmartInteger is less than the other SmartInteger.
         * 
         * @return boolean result of less than operator
         * */
        bool operator<(SmartInteger rhs);

        /**
         * @brief an overloaded operator > that returns whether or not the value of the left hand 
         * side SmartInteger is greater than the other SmartInteger.
         * 
         * @return boolean result of greater than operator
         * */
        bool  operator>(SmartInteger rhs);

        /**
         * @brief an overloaded operator <= that returns whether or not the value of the left 
         * hand side SmartInteger is less than or equal to the other SmartInteger.
         * 
         * @return boolean result of <= operator
         * */
        bool operator<=(SmartInteger rhs);

        /**
         * @brief an overloaded operator >= that returns whether or not the value of the left hand 
         * side SmartInteger is greater than or equal to the other SmartInteger.
         * 
         * @return boolean result of >= operator
         * */
        bool operator>=(SmartInteger rhs);

        /**
         * @brief an overloaded operator == that returns whether or not the value of the left hand 
         * side SmartInteger is equal to the other SmartInteger.
         * 
         * @return boolean result of == operator
         * */
        bool operator==(SmartInteger rhs);

        /**
         * @brief an overloaded operator != that returns whether or not the value of the left hand 
         * side SmartInteger is not equal to the other SmartInteger.
         * 
         * @return boolean result of != operator
         * */
        bool operator!=(SmartInteger rhs);

        /**
         * @brief an overloaded operator + that returns a SmartInteger that is the sum of two 
         * SmartIntegers. This function should detect overflow and throw an std::exception if the 
         * addition causes an integer overflow. 
         * 
         * @throws std::exception
         * @return SmartInteger result from adding the two SmartIntegers
         * */
        SmartInteger operator+(SmartInteger rhs);
};

#endif // A5_SMARTINTEGER_HPP