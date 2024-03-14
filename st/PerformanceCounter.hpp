#pragma once

#include <functional>

#include "st/DateTime.hpp"

namespace st
{
    class PerformanceCounter
    {
        using TestFunc = std::function<bool(void)>;
       
    public:
        auto Now() const
        {
            return st::DateTime::Now();
        }

        auto Check(const bool isTotal = false)
        {
            const auto now = st::DateTime::Now();

            if (isTotal)
            {
                return (now - _start).ToMilliseconds();
            }
            else
            {
                auto diff = now - _prev;
                _prev = now;
                return diff.ToMilliseconds();
            }
        }

        void Measure(TestFunc f) const
        {
            static constexpr st::StringView dividerOut_{_T("====================================================\n")};       
            static constexpr st::StringView dividerIn_{_T("----------------------------------------------------\n")};

            if (f)
            {
                auto start = Now();

                tcout << dividerOut_;
                tcout << _T("PerformanceCheck Start : ") << start << tendl;

                tcout << dividerIn_;
                auto result = f();
                tcout << dividerIn_;

                auto end = Now();
                auto diff = end - start;

                tcout << _T("PerformanceCheck Result : ") << std::boolalpha << result << std::noboolalpha << tendl;
                tcout << _T("PerformanceCheck Duration : ") << diff.ToMilliseconds() << tendl;
                tcout << _T("PerformanceCheck End : ") << end << tendl;
                tcout << dividerOut_ << tendl;

            }
        }

    private:
        const st::DateTime _start{st::DateTime::Now()};
        st::DateTime _prev{st::DateTime::Now()};
    };
}
