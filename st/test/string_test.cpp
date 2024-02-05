#include "./string.h"

#include <iostream>

#include "st/String.hpp"
#include "st/DateTime.hpp"

namespace st::test
{
    bool test_String()
    {
        tcout << __FUNCTIONW__ << tendl;

        auto str = st::String();
        str = _T("aaa");
        str += _T("bbb");
        str.append(_T("bbb"));
        tcout << str << tendl;

        auto strC = st::String(str);
        tcout << str << _T(" ") << strC << tendl;

        auto strCA = str;
        tcout << str << _T(" ") << strCA << tendl;

        auto strM = st::String(std::move(str));
        tcout << str << _T(" ") << strM << tendl;

        auto strMA = std::move(str);
        tcout << str << _T(" ") << strMA << tendl;
        return true;
    }

    bool test_StringBuilder()
    {
        tcout << __FUNCTIONW__ << tendl;
        
        tcout << st::String(_T("aaa"), 1, _T("bbb"), 1.1f, st::String(_T("ccc")), -1, 0) << tendl;
        tcout << st::String(st::DateTime::Now(), st::DateTime::Now(), st::DateTime::Now()) << tendl;
        return true;
    }
}
