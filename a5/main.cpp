#include "SmartInteger.hpp"

#include <iostream>
#include <limits>

int main() {
    // std::cout << "Constructing n1 and n2..." << std::endl;
    // SmartInteger n1(3);
    // SmartInteger n2;
    // std::cout << "n1.getValue() should be 3: " << n1.getValue() << std::endl;
    // std::cout << "n2.getValue() should be 0: " << n2.getValue() << std::endl;
    // std::cout << std::endl;


    // // No need to implement custom copy assignment operator - this should just work
    // std::cout << "Changing value of n2..." << std::endl;
    // n2 = 3;
    // std::cout << "n2.getValue() should be 3: " << n2.getValue() << std::endl;
    // std::cout << std::endl;

    // // No need to implement custom copy constructor - this should just work
    // std::cout << "Constructing n3..." << std::endl;
    // SmartInteger n3(n2);
    // std::cout << "n3.getValue() should be 3: " << n3.getValue() << std::endl;

    // std::cout << std::endl;

    // // Add more code here to test SmartInteger here!

    // SmartInteger n4(2);
    // const SmartInteger n5(-3);
    // const SmartInteger n6(4);
    // (n4+=n5)+=n6;
    // std::cout << n4 << std::endl;

    
    SmartInteger n1(2);
    SmartInteger n2(-3);
    SmartInteger n3(std::numeric_limits<int>::max());
    SmartInteger n4(std::numeric_limits<int>::min());

    std::cout << n1 - n4 << std::endl;

    
    // SmartInteger n4(2);
    // const SmartInteger n5(-3);
    // const SmartInteger n6(4);
    // (n4 += n5);
    // n4 += n6;
    // std::cout << n4 << std::endl;

    return 0;
}
