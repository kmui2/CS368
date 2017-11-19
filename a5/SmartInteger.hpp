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
         * 
         * @param the int to set the integer value to
         * */
        SmartInteger(const int num);

        /**
         * @brief This function is a simple getter that returns the integer value of the 
         * SmartInteger.
         * 
         * @return the SmartInteger as an int
         * */
        const int getValue();

        /**
         * @brief an overloaded operator << for ostream and SmartInteger. This should 
         * display the integer value of the SmartInteger as if it were calling getValue().
         * 
         * @param the outstream to print
         * @return the out stream
         * */
        std::ostream& operator<<(std::ostream& os);

        /**
         * @brief an overloaded operator < that returns whether or not the value of the left hand s
         * ide SmartInteger is less than the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of less than operator
         * */
        const bool operator<(const SmartInteger rhs);

        /**
         * @brief an overloaded operator > that returns whether or not the value of the left hand 
         * side SmartInteger is greater than the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of greater than operator
         * */
        const bool  operator>(const SmartInteger rhs);

        /**
         * @brief an overloaded operator <= that returns whether or not the value of the left 
         * hand side SmartInteger is less than or equal to the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of <= operator
         * */
        const bool operator<=(const SmartInteger rhs);

        /**
         * @brief an overloaded operator >= that returns whether or not the value of the left hand 
         * side SmartInteger is greater than or equal to the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of >= operator
         * */
        const bool operator>=(const SmartInteger rhs);

        /**
         * @brief an overloaded operator == that returns whether or not the value of the left hand 
         * side SmartInteger is equal to the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of == operator
         * */
        const bool operator==(const SmartInteger rhs);

        /**
         * @brief an overloaded operator != that returns whether or not the value of the left hand 
         * side SmartInteger is not equal to the other SmartInteger.
         * 
         * @param the right hand side of the operator equation
         * @return boolean result of != operator
         * */
        const bool operator!=(const SmartInteger rhs);

        /**
         * @brief an overloaded operator + that returns a SmartInteger that is the sum of two 
         * SmartIntegers. This function should detect overflow and throw an std::exception if the 
         * addition causes an integer overflow. 
         * 
         * @param the right hand side of the operator equation
         * @throws std::exception
         * @return SmartInteger result from adding the two SmartIntegers
         * */
        const SmartInteger operator+(const SmartInteger rhs);

        /**
         * @brief an overloaded operator - that returns a SmartInteger that is the difference of 
         * two SmartIntegers. This function should detect overflow and throw an std::exception 
         * if the subtraction causes an integer overflow.
         * 
         * @param the right hand side of the operator equation
         * @throws std::exception
         * @return SmartInteger result from subtracting the two SmartIntegers
         * */
        const SmartInteger operator-(const SmartInteger rhs);

        /**
         * @brief an overloaded operator * that returns a SmartInteger that is the product of two 
         * SmartIntegers. This function should detect overflow and throw an std::exception if the 
         * multiplication causes an integer overflow. 
         * 
         * @param the right hand side of the operator equation
         * @throws std::exception
         * @return SmartInteger result from multiplying the two SmartIntegers
         * */
        const SmartInteger operator*(const SmartInteger rhs);

        /**
         * @brief an overloaded operator += that adds the right operand and the left operand and 
         * stores the new value in the left operand. This function should also throw an 
         * std::exception in the case of overflow, and the internal value should not be changedin 
         * the case of overflow.
         * 
         * @param the right hand side of the operator equation
         * @return SmartInteger result from adding and assigning another SmartInteger
         * */
        const SmartInteger operator+=(const SmartInteger rhs);

        /**
         * @brief an overloaded operator -= that subtracts the right operand from the left operand 
         * and stores the new value in the left operand. This function should also throw an 
         * std::exception in the case of overflow, and the internal value should not be changedin 
         * the case of overflow.
         * 
         * @param the right hand side of the operator equation
         * @return SmartInteger result from subtracting and assigning another SmartInteger
         * */
        const SmartInteger operator-=(const SmartInteger rhs);

        /**
         * @brief an overloaded operator *= that multiplies the right operand and the left operand 
         * and stores the new value in the left operand. This function should also throw an 
         * std::exception in the case of overflow, and the internal value should not be changed 
         * in the case of overflow.
         * 
         * @param the right hand side of the operator equation
         * @return SmartInteger result from multiplying and assigning another SmartInteger
         * */
        const SmartInteger operator*=(const SmartInteger rhs);

        /**
         * @brief an overloaded pre-increment operator, ++, that adds 1 to the current SmartInteger 
         * and returns the changed SmartInteger. This function should also throw an std::exception 
         * in the case of overflow, and the internal value should not be changed in the case of 
         * overflow.
         * 
         * @return SmartInteger result from preprending the SmartInteger
         * */
        const SmartInteger ++operator();

        /**
         * @brief an overloaded pre-decrement operator, --, that subtracts 1 from the current 
         * SmartInteger and returns the changed SmartInteger. This function should also throw an 
         * std::exception in the case of overflow, and the internal value should not be changedin 
         * the case of overflow.
         * 
         * @return SmartInteger result from preprending the SmartInteger
         * */
        const SmartInteger --operator();
};

#endif // A5_SMARTINTEGER_HPP