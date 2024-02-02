#include "./datetime_test.h"

#include "st/DateTime.hpp"

namespace st::test{
    bool test_DateTime(){
        auto str_now = DateTime::Now().To_string();

        tout << str_now << tendl;

        return false;
    }
}


