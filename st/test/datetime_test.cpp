#include "./datetime_test.h"

#include <iostream>

#include "st/DateTime.hpp"

namespace st::test{
    bool test_DateTime(){
        auto str_now = DateTime::Now().To_string();

        std::cout << str_now << std::endl;

        return false;
    }
}


