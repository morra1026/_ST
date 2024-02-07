#include "./test.h"

#include "st/String.hpp"
#include "st/DateTime.hpp"

#include "st/PerformanceCounter.hpp"

#include "st/MemoryAllocator.hpp"
#include <list>

namespace st::test
{
    bool test_String()
    {
        tcout << __FUNCTIONW__ << tendl;

        auto str = st::String();
        str = _T("aaa");
        str += _T("bbb");
        str.append(_T("ccc"));
        tcout << str << tendl;

        auto strC = st::String(str);
        tcout << str << _T(" ") << strC << tendl;

        auto strCA = str;
        tcout << str << _T(" ") << strCA << tendl;

        auto strM = st::String(std::move(str));
        tcout << str << _T(" ") << strM << tendl;

        auto strMA = std::move(str);
        tcout << str << _T(" ") << strMA << tendl;

        auto strDatetime = st::String(st::DateTime::Now());
        tcout << strDatetime << tendl;
        return true;
    }

    bool test_StringBuilder()
    {
        tcout << __FUNCTIONW__ << tendl;

        tcout << st::String::Builder(_T("aaa"), 1, _T("bbb"), 1.1f, st::String(_T("ccc")), -1, 0) << tendl;
        tcout << st::String::Builder(st::DateTime::Now(), st::DateTime::Now(), st::DateTime::Now()) << tendl;
        return true;
    }

    bool test_DateTime()
    {
        tcout << __FUNCTIONW__ << tendl;

        auto str_now = DateTime::Now().To_string();

        tcout << str_now << tendl;

        return false;
    }

    bool test_MemoryAllocator()
    {
        tcout << __FUNCTIONW__ << tendl;

        auto stmalloc = st::MemoryAllocator<int>{};
        auto p = stmalloc.allocate(1);
        stmalloc.deallocate(p, 1);

        auto v = std::vector<int, st::MemoryAllocator<int>>{};
        auto v2 = std::vector<int, st::MemoryAllocator<int>>{};
        auto l = std::list<int, st::MemoryAllocator<int>>{};

        tcout << _T("v == v2 : ") << (v == v2) << tendl;

        return false;
    }

    void test_main()
    {
        st::PerformanceCounter pfc{};

        constexpr st::StringView divider{_T("=================================================\n")};

        tcout << divider << _T("PerformanceCheck Start : ") << st::test::test_String()             << _T(", ") << pfc.Check() << tendl << divider << tendl;
        tcout << divider << _T("PerformanceCheck Start : ") << st::test::test_DateTime()           << _T(", ") << pfc.Check() << tendl << divider << tendl;
        tcout << divider << _T("PerformanceCheck Start : ") << st::test::test_StringBuilder()      << _T(", ") << pfc.Check() << tendl << divider << tendl;
        tcout << divider << _T("PerformanceCheck Start : ") << st::test::test_MemoryAllocator()    << _T(", ") << pfc.Check() << tendl << divider << tendl;
    }
}
