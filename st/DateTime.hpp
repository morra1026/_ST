#pragma once

#include <chrono>
#include <format>

#include <windows.h>

#include "String.hpp"

namespace st
{
    using namespace std::chrono_literals;

    class Duration : public std::chrono::system_clock::duration
    {
    public:
        Duration() = default;
        Duration(const Duration&) = default;
        Duration& operator=(const Duration&) = default;
        Duration(Duration&&) = default;
        Duration& operator=(Duration&&) = default;
        ~Duration() = default;

        template <class _Rep, class _Period>
        Duration(const std::chrono::duration<_Rep, _Period>& d) : 
            std::chrono::system_clock::duration(std::chrono::duration_cast<std::chrono::system_clock::duration>(d)) {}

        std::chrono::milliseconds ToMilliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(*this); }
        std::chrono::seconds ToSeconds() const { return std::chrono::duration_cast<std::chrono::seconds>(*this); }
        std::chrono::minutes ToMinutes() const { return std::chrono::duration_cast<std::chrono::minutes>(*this); }
        std::chrono::hours ToHours() const { return std::chrono::duration_cast<std::chrono::hours>(*this); }
        std::chrono::days ToDays() const { return std::chrono::duration_cast<std::chrono::days>(*this); }
        std::chrono::weeks ToWeeks() const { return std::chrono::duration_cast<std::chrono::weeks>(*this); }
    };

    using LocalTime = std::chrono::local_time<std::chrono::system_clock::duration>;
    using SysTime = std::chrono::sys_time<std::chrono::system_clock::duration>;

    class DateTime : public LocalTime
    {
    public:
        enum class eFormat
        {
            YYYYMMDD,
            YYYYMMDDhh,
            YYYYMMDDhhmm,
            YYYYMMDDhhmmss,
        };

        enum class eWEEK
        {
            SUN = 0, // 일
            MON,     // 월
            TUE,     // 화
            WED,     // 수
            THU,     // 목
            FRI,     // 금
            SAT,     // 토
        };

        static constexpr bool IsLeapYear(const unsigned short year)
        {
            if (year % 4 == 0)
            {
                if (year % 100 == 0)
                {
                    if (year % 400 == 0)
                        return true;
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return false;
        }

        static constexpr LocalTime To_local_time(const unsigned int YYYY, const unsigned int MM, const unsigned int DD,
                                                 const unsigned int hh = 0, const unsigned int mm = 0, const unsigned int ss = 0, const unsigned int ms = 0)
        {
            const auto ymd = std::chrono::year_month_day{std::chrono::year(YYYY) / std::chrono::month(MM) / std::chrono::day(DD)};
            if (ymd.ok())
                return std::chrono::local_days{ymd} + std::chrono::hours(hh) + std::chrono::minutes(mm) + std::chrono::seconds(ss) + std::chrono::milliseconds(ms);
            else
                return {};
        }

        static constexpr LocalTime To_local_time(const SYSTEMTIME &st)
        {
            return To_local_time(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        }

        static constexpr LocalTime To_local_time(const __int64 value, const eFormat format = eFormat::YYYYMMDD)
        {
            unsigned int YYYY{};
            unsigned int MM{};
            unsigned int DD{};
            unsigned int hh{};
            unsigned int mm{};
            unsigned int ss{};

            switch (format)
            {
            case eFormat::YYYYMMDD:
            {
                if (value < 19700101)
                    return {};

                YYYY = static_cast<unsigned int>(value / 10000);
                MM = static_cast<unsigned int>(value % 10000 / 100);
                DD = static_cast<unsigned int>(value % 100);
                break;
            }

            case eFormat::YYYYMMDDhh:
            {
                if (value < 1970010100)
                    return {};

                YYYY = static_cast<unsigned int>(value / 1000000);
                MM = static_cast<unsigned int>(value % 1000000 / 10000);
                DD = static_cast<unsigned int>(value % 10000 / 100);
                hh = static_cast<unsigned int>(value % 100);
                break;
            }
            case eFormat::YYYYMMDDhhmm:
            {
                if (value < 197001010000)
                    return {};

                YYYY = static_cast<unsigned int>(value / 100000000);
                MM = static_cast<unsigned int>(value % 100000000 / 1000000);
                DD = static_cast<unsigned int>(value % 1000000 / 10000);
                hh = static_cast<unsigned int>(value % 10000 / 100);
                mm = static_cast<unsigned int>(value % 100);
                break;
            }
            case eFormat::YYYYMMDDhhmmss:
            {
                if (value < 19700101000000)
                    return {};

                YYYY = static_cast<unsigned int>(value / 10000000000);
                MM = static_cast<unsigned int>(value % 10000000000 / 100000000);
                DD = static_cast<unsigned int>(value % 100000000 / 1000000);
                hh = static_cast<unsigned int>(value % 1000000 / 10000);
                mm = static_cast<unsigned int>(value % 10000 / 100);
                ss = static_cast<unsigned int>(value % 100);
                break;
            }
            default:
            {
                return LocalTime{};
            }
            }

            return To_local_time(YYYY, MM, DD, hh, mm, ss);
        }

        static constexpr LocalTime To_local_time(const SysTime &systime)
        {
            // 강제로 sys_time(UTC)에 +9해서 사용
            return LocalTime{systime.time_since_epoch() + 9h};
        }

        static constexpr SysTime To_sys_time(const LocalTime &localtime)
        {
            // 강제로 local_time에 -9해서 사용
            return SysTime{localtime.time_since_epoch() - 9h};
        }

        constexpr DateTime() = default;
        constexpr DateTime(const std::chrono::system_clock::duration &d) : LocalTime(d) {}
        constexpr DateTime(const LocalTime &tp) : LocalTime(tp) {}
        constexpr DateTime(const SysTime &tp) : LocalTime(DateTime::To_local_time(tp)) {}
        constexpr DateTime(const time_t &t) : LocalTime(DateTime::To_local_time(std::chrono::system_clock::from_time_t(t))) {}
        // constexpr DateTime(const SYSTEMTIME &st) : LocalTime(::System::To_local_time(st)) {}

        // create
        static constexpr DateTime Now() { return DateTime{DateTime::To_local_time(std::chrono::system_clock::now())}; } // return chrono::zoned_time{ chrono::current_zone(), systime }.get_local_time();	//zoned_time을 사용하면 Exception이 발생하면서 모듈을 못찾는다-_- OS문제인가??

        static constexpr DateTime YYYYMMDD(int YYYYMMDD) { return DateTime{DateTime::To_local_time(YYYYMMDD, eFormat::YYYYMMDD)}; }
        static constexpr DateTime YYYYMMDDhh(unsigned int YYYYMMDDhh) { return DateTime{DateTime::To_local_time(YYYYMMDDhh, eFormat::YYYYMMDDhh)}; }    // 꼭 필요한가? 정리차원에서 없애는게?
        static constexpr DateTime YYYYMMDDhhmm(__int64 YYYYMMDDhhmm) { return DateTime{DateTime::To_local_time(YYYYMMDDhhmm, eFormat::YYYYMMDDhhmm)}; } // 꼭 필요한가? 정리차원에서 없애는게?
        static constexpr DateTime YYYYMMDDhhmmss(__int64 YYYYMMDDhhmmss) { return DateTime{DateTime::To_local_time(YYYYMMDDhhmmss, eFormat::YYYYMMDDhhmmss)}; }

        static constexpr DateTime YYYYMMDD(const st::String &strYYYYMMDD) { return strYYYYMMDD.empty() ? DateTime{} : DateTime::YYYYMMDD(::_ttoi(strYYYYMMDD.c_str())); }

        static DateTime String(const st::String str) //"YYYY-MM-DD hh:mm:ss"
        {
            if (str.length() != 19)
                return DateTime{};

            const auto year = ::_ttoi(str.substr(0, 4).c_str());
            const auto month = ::_ttoi(str.substr(5, 2).c_str());
            const auto day = ::_ttoi(str.substr(8, 2).c_str());
            const auto hour = ::_ttoi(str.substr(11, 2).c_str());
            const auto min = ::_ttoi(str.substr(14, 2).c_str());
            const auto sec = ::_ttoi(str.substr(17, 2).c_str());

            return DateTime{DateTime::To_local_time(year, month, day, hour, min, sec)};
        }
        static DateTime String_Date(const st::String str) //"YYYY-MM-DD"
        {
            if (str.length() != 10)
                return DateTime{};

            const auto year = ::_ttoi(str.substr(0, 4).c_str());
            const auto month = ::_ttoi(str.substr(5, 2).c_str());
            const auto day = ::_ttoi(str.substr(8, 2).c_str());

            return DateTime{DateTime::To_local_time(year, month, day)};
        }

    private:
        inline constexpr auto toYMD() const { return std::chrono::year_month_day{std::chrono::time_point_cast<std::chrono::days>(*this)}; }
        inline constexpr auto toYMW() const { return std::chrono::year_month_weekday{std::chrono::time_point_cast<std::chrono::days>(*this)}; }
        inline constexpr auto toHMS() const { return std::chrono::hh_mm_ss{*this - ToDate()}; }
        inline constexpr auto isValidCalendar() const { return toYMD().ok() && toYMW().ok(); }

    public:
        // convert
        const time_t To_time_t() const { return std::chrono::system_clock::to_time_t(this->To_sys_time()); }
        // constexpr SYSTEMTIME ToSYSTEMTIME() const { return {Year(), Month(), static_cast<WORD>(Week()), Day(), Hour(), Min(), Sec(), MiliSec()}; }
        constexpr SysTime To_sys_time() const { return DateTime::To_sys_time(*this); }
        constexpr LocalTime To_local_time() const { return LocalTime{this->time_since_epoch()}; }

        // 오늘 0시로 변경 to YYYY-MM-DD 00:00:00
        constexpr DateTime ToDate() const
        {
            return DateTime{std::chrono::time_point_cast<std::chrono::system_clock::duration>(std::chrono::time_point_cast<std::chrono::days>(*this))};
        }
        // 8시 기준으로 어제 혹은 오늘의 8시로 변경 to YYYY-MM-DD 08:00:00
        constexpr DateTime To8AM() const
        {
            auto dt = *this;
            if (dt.Hour() < 8)
            {
                dt -= 24h;
            }

            return dt.ToDate() += 8h;
        }

        constexpr int Tohhmm() const
        {
            return Hour() * 100 +
                   Min();
        }
        constexpr int Tohhmmss() const
        {
            return Hour() * 10000 +
                   Min() * 100 +
                   Sec();
        }
        constexpr int ToYYMMDDhh() const
        {
            return Year() % 100 * 1000000 +
                   Month() * 10000 +
                   Day() * 100 +
                   Hour();
        }
        constexpr __int64 ToYYMMDDhhmmss() const
        {
            return static_cast<__int64>(Year() % 100) * 10000000000 +
                   static_cast<__int64>(Month()) * 100000000 +
                   static_cast<__int64>(Day()) * 1000000 +
                   static_cast<__int64>(Hour()) * 10000 +
                   static_cast<__int64>(Min()) * 100 +
                   static_cast<__int64>(Sec());
        }
        constexpr int ToYYYYMMDD() const
        {
            return Year() * 10000 +
                   Month() * 100 +
                   Day();
        }
        constexpr int ToYYYYMMDDhh() const
        {
            return Year() * 1000000 +
                   Month() * 10000 +
                   Day() * 100 +
                   Hour();
        }
        constexpr __int64 ToYYYYMMDDhhmmss() const
        {
            return static_cast<__int64>(Year()) * 10000000000 +
                   static_cast<__int64>(Month()) * 100000000 +
                   static_cast<__int64>(Day()) * 1000000 +
                   static_cast<__int64>(Hour()) * 10000 +
                   static_cast<__int64>(Min()) * 100 +
                   static_cast<__int64>(Sec());
        }

        st::String ToString() const { return std::format(_T("{:%F %T}"), *this); } //"YYYY-MM-DD hh:mm:ss"
        st::String ToString(const st::FormatString<const st::DateTime&> format) const { return std::format(format, *this); }
        st::String ToString_Date() const { return std::format(_T("{:%F}"), *this); } //"YYYY-MM-DD"
        st::String ToString_Time() const { return std::format(_T("{:%T}"), *this); } //"hh:mm:ss"
        st::String ToDB() const { return std::format(_T("{0:%F}T{0:%T}"), *this); } //"YYYY - MM - DDThh:mm:ss:mmm"

        // get
        inline constexpr unsigned short Year() const { return static_cast<unsigned short>(toYMD().year().operator int()); }
        inline constexpr unsigned short Month() const { return static_cast<unsigned short>(toYMD().month().operator unsigned int()); }
        inline constexpr unsigned short Day() const { return static_cast<unsigned short>(toYMD().day().operator unsigned int()); }
        inline constexpr eWEEK Week() const { return static_cast<eWEEK>(toYMW().weekday().c_encoding()); }
        inline constexpr unsigned short Hour() const { return static_cast<unsigned short>(toHMS().hours().count()); }
        inline constexpr unsigned short Min() const { return static_cast<unsigned short>(toHMS().minutes().count()); }
        inline constexpr unsigned short Sec() const { return static_cast<unsigned short>(toHMS().seconds().count()); }
        inline constexpr unsigned short MiliSec() const { return static_cast<unsigned short>(std::chrono::duration_cast<std::chrono::milliseconds>(toHMS().subseconds()).count()); }

        // 연, 월은 주로 환산해서 계산하기로 한다.
        //#todo : https://en.cppreference.com/w/cpp/chrono/year_month_day/operator_arith 참고해서 개선해보자
        DateTime AddYears(const int years) const  = delete;
        DateTime AddMonths(const int months) const = delete;    
        //  // arithmetic
        //  //  연대기적 계산법 - https://stackoverflow.com/questions/43010362/c-add-months-to-chronosystem-clocktime-point/43018120#43018120
        //  //  AddYears, AddMonths의 경우 한달:30.436875일, 일년365.2425일 으로 계산하고 있는 점 참고~
        //  DateTime AddYears(const int years) const { return DateTime{*this + std::chrono::years(years)}; }
        //  DateTime AddMonths(const int months) const { return DateTime{*this + std::chrono::months(months)}; }

        // // 달력 계산법
        // DateTime AddYears_CalendricalComputation(const int years) const
        // {
        //     return AddMonths_CalendricalComputation(years * 12);
        // }
        // DateTime AddMonths_CalendricalComputation(const int months) const
        // {
        //     DateTime ret = DateTime{*this};
        //     // 한달씩 더해나갈 거다
        //     for (int roof = 0, extraDays = 0; roof < months; roof++)
        //     {
        //         auto year{ret.Year()}, month{ret.Month()}, day{ret.Day()};
        //         int lastDayOfMonth = GetdaysOfMonth(year, month);
        //         NextMonth(year, month);
        //         int lastDayOfMonth_forNextMonth = GetdaysOfMonth(year, month);

        //         // 다음달 같은 날의 day가 없는경우도 있다. 1/31 다음달 같은 날은? 2/31일은 없으니 2/28 이나 2/29로  보정..
        //         if (day + extraDays > lastDayOfMonth_forNextMonth)
        //         {
        //             // 다음달 끝날이 짧아서 미처 더하지 못한 날이 발생할 경우
        //             // 미처 더하지 못한 날을 따로 저장해두고 나머지만 더하자
        //             extraDays = day + extraDays - lastDayOfMonth_forNextMonth;
        //             ret = ret.AddDay(lastDayOfMonth - extraDays);
        //         }
        //         else
        //         {
        //             // 미처 더하지 못한날을 포함해도 다 더하면 되는 경우
        //             // 미처 더하지 못한날들을 다 더하고  털어버리자
        //             ret = ret.AddDay(lastDayOfMonth + extraDays);
        //             extraDays = 0;
        //         }

        //         // 				std::cout << "//\t" << roof << ":\t" << lastDayOfMonth << "\t" << lastDayOfMonth_forNextMonth << "\t"
        //         // 					<< day << "\t" << extraDays << "\t" << ret.ToString() << std::endl;
        //     }
        //     return ret;
        // }

        DateTime AddWeeks(const int weeks) const { return DateTime{*this + std::chrono::weeks(weeks)}; }
        DateTime AddDay(const int day) const { return DateTime{*this + std::chrono::days(day)}; }
        DateTime AddHour(const int hour) const { return DateTime{*this + std::chrono::hours(hour)}; }
        DateTime AddMin(const int min) const { return DateTime{*this + std::chrono::minutes(min)}; }
        DateTime AddSec(const int sec) const { return DateTime{*this + std::chrono::seconds(sec)}; }
        // operator + - += -= 도 넣으면 좋을거 같은데?
        template <class _Rep, class _Period>
        constexpr DateTime &operator+=(const std::chrono::duration<_Rep, _Period> &duration)
        {
            *this = DateTime{this->time_since_epoch() + duration};
            return *this;
        }
        template <class _Rep, class _Period>
        constexpr DateTime &operator-=(const std::chrono::duration<_Rep, _Period> &duration)
        {
            *this = DateTime{this->time_since_epoch() - duration};
            return *this;
        }

        // compare
        static int Compare(const DateTime &lhs, const DateTime &rhs) { return (lhs <=> rhs)._Value; }

        const bool IsZero() { return this->time_since_epoch() == std::chrono::system_clock::duration::zero(); }

        // this와 after 사이에 week 가 있는지 체크
        inline const bool IsWeekChange(const DateTime &after, const eWEEK week = eWEEK::THU) const
        {
            if (*this < after)
            {
                auto diff = std::chrono::abs(Duration(after - *this).ToDays());
                if (0 < diff.count())
                {
                    if (7 <= diff.count())
                        return true; // 두 날짜의 차이가 7일 이상이면
                    else
                    {
                        // 요일을 가져오고
                        auto weekBefore = this->Week();

                        // 시작일 다음 목요일(base)를 구해서
                        int dayAdd = 0;
                        if (static_cast<int>(weekBefore) < static_cast<int>(week))
                        {
                            // 기준 요일 이전
                            dayAdd = static_cast<int>(week) - static_cast<int>(weekBefore);
                        }
                        else
                        {
                            // 기준 요일 이후
                            dayAdd = static_cast<int>(week) + 7 - static_cast<int>(weekBefore);
                        }
                        auto base = *this + std::chrono::days(dayAdd);

                        // after가 base 보다 크면 OK
                        if (base <= after)
                            return true;
                    }
                }
            }

            return false;
        }
    };

    // DateTime compare
    inline bool operator==(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) == 0; }
    inline bool operator!=(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) != 0; }
    inline bool operator<(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) < 0; }
    inline bool operator>(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) > 0; }
    inline bool operator<=(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) <= 0; }
    inline bool operator>=(const DateTime &lhs, const DateTime &rhs) { return DateTime::Compare(lhs, rhs) >= 0; }

    // DateTime arithmetic
    template <class _Rep, class _Period>
    inline constexpr DateTime operator+(DateTime lhs, const std::chrono::duration<_Rep, _Period> &rhs) { return lhs += rhs; }
    template <class _Rep, class _Period>
    inline constexpr DateTime operator-(DateTime lhs, const std::chrono::duration<_Rep, _Period> &rhs) { return lhs -= rhs; }

    inline Duration operator-(const DateTime &lhs, const DateTime &rhs) { return lhs.To_local_time() - rhs.To_local_time(); }
}

template <>
struct std::formatter<st::DateTime, st::Char> : std::formatter<st::LocalTime, st::Char>
{
    template <typename FormatContext>
    auto format(const st::DateTime &dt, FormatContext &ctx) const -> decltype(ctx.out())
    {
        return std::formatter<st::LocalTime, st::Char>::format(dt.To_local_time(), ctx);
    }
};