#pragma once

#include "st/DateTime.hpp"

namespace st
{
    class PerformanceCounter
    {
    public:
        auto Check(const bool isTotal = false)
        {
            const auto now = st::DateTime::Now();

            if (isTotal)
            {
                return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_);
            }
            else
            {
                auto diff = now - prev_;
                prev_ = now;
                return std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            }
        }

    private:
        const st::DateTime start_{st::DateTime::Now()};
        st::DateTime prev_{st::DateTime::Now()};
    };
}
