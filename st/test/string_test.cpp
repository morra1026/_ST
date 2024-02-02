#include "./string.h"

#include <iostream>

#include "st/String.hpp"

namespace st::test{
    bool test_String()
    {
        // st::String::Builder("aaa", 1, "bbb");

        {
            auto str = std::wstring();
            str = _T("aaa");
        }

        {
            auto str = st::String();
             str = _T("aaa");
            auto strC = st::String(str);
            auto strCA = str;
            auto strM = st::String(std::move(str));
            auto strMA = std::move(str);
        }
        return false;
    }
}
