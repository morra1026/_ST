
#include "st/test/string_test.h"
#include "st/test/datetime_test.h"

#include "st/PerformanceCounter.hpp"

int main()
{
    st::PerformanceCounter pfc{};

    st::test::test_String();

    tcout << _T("test_String :") << pfc.Check() << tendl;

    st::test::test_DateTime();

    tcout << _T("test_DateTime :") << pfc.Check() << tendl;

    st::test::test_StringBuilder();

    tcout << _T("test_StringBuilder :") << pfc.Check() << tendl;

    return 0;
} 