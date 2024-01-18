#include <iostream>

#include "st/test/datetime_test.h"

#include "st/PerformanceCounter.hpp"

int main()
{
    st::PerformanceCounter pfc{};

    st::test::test_DateTime();

    std::cout << "1 :" << pfc.Check() << std::endl;

    Sleep(1002);

    std::cout << "2 :" << pfc.Check() << std::endl;
    std::cout << "2 :" << pfc.Check() << std::endl;
    std::cout << "2 :" << pfc.Check() << std::endl;
    std::cout << "2 :" << pfc.Check() << std::endl;
    std::cout << "2 :" << pfc.Check() << std::endl;
    std::cout << "2 :" << pfc.Check() << std::endl;


    return 0;
} 