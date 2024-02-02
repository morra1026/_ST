#include <iostream>

#include "st/test/string_test.h"
#include "st/test/datetime_test.h"

#include "st/PerformanceCounter.hpp"

int main()
{


    st::PerformanceCounter pfc{};

    st::test::test_String();

    tout << _T("test_String :") << pfc.Check() << tendl;

    st::test::test_DateTime();

    tout << _T("test_DateTime :") << pfc.Check() << tendl;

    Sleep(1002);
    
    tout << _T("2 :") << pfc.Check() << tendl;
    tout << _T("2 :") << pfc.Check() << tendl;
    tout << _T("2 :") << pfc.Check() << tendl;
    tout << _T("2 :") << pfc.Check() << tendl;
    tout << _T("2 :") << pfc.Check() << tendl;
    tout << _T("2 :") << pfc.Check() << tendl;


    return 0;
} 