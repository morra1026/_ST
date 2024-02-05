#include "./datetime_test.h"

#include "st/DateTime.hpp"

namespace st::test{
    bool test_DateTime(){
        tcout << __FUNCTIONW__ << tendl;

        auto str_now = DateTime::Now().To_string();

        tcout << str_now << tendl;

        return false;
    }
}


