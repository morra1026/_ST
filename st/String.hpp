#pragma once

#include <string>
#include <string_view>
#include <format>
#include <iostream>

#include <tchar.h>

// #include <type_traits>

#ifdef _UNICODE
#define tcout std::wcout
#else
#define tcout std::cout
#endif
#define tendl std::endl


namespace st
{
    using namespace std::literals;

    using Char = _TCHAR;
    using _String = std::basic_string<Char>;
    using StringView = std::basic_string_view<Char>;

    using _tios = std::basic_ios<Char, std::char_traits<Char>>;
    using _tstreambuf = std::basic_streambuf<Char, std::char_traits<Char>>;
    using _tistream = std::basic_istream<Char, std::char_traits<Char>>;
    using _tostream = std::basic_ostream<Char, std::char_traits<Char>>;
    using _tiostream = std::basic_iostream<Char, std::char_traits<Char>>;
    using _tistringstream = std::basic_istringstream<Char, std::char_traits<Char>, std::allocator<Char>>;
    using _tstringbuf = std::basic_stringbuf<Char, std::char_traits<Char>, std::allocator<Char>>;
    using _tostringstream = std::basic_ostringstream<Char, std::char_traits<Char>, std::allocator<Char>>;
    using _tstringstream = std::basic_stringstream<Char, std::char_traits<Char>, std::allocator<Char>>;
    using _tfilebuf = std::basic_filebuf<Char, std::char_traits<Char>>;
    using _tifstream = std::basic_ifstream<Char, std::char_traits<Char>>;
    using _tofstream = std::basic_ofstream<Char, std::char_traits<Char>>;
    using _tfstream = std::basic_fstream<Char, std::char_traits<Char>>;
#if _HAS_CXX20
    using _tsyncbuf = std::basic_syncbuf<Char>;
    using _tosyncstream = std::basic_osyncstream<Char>;
#endif // _HAS_CXX20
#if _HAS_CXX23
    using _tspanbuf = std::basic_spanbuf<Char>;
    using _tispanstream = std::basic_ispanstream<Char>;
    using _tospanstream = std::basic_ospanstream<Char>;
    using _tspanstream = std::basic_spanstream<Char>;
#endif // _HAS_CXX23

    class String : public _String
    {
        static constexpr Char default_delimiter_ = _T('\t');
        static constexpr StringView default_placeholder_ = _T("{}");

    public:
        String() = default;
        String(const String &) = default;
        String &operator=(const String &) = default;
        String(String &&) = default;
        String &operator=(String &&) = default;
        ~String() = default;

        String(const Char *pStr) : _String(pStr){};
        String(const _String &str) : _String(str){};

        friend _tostream &operator<<(_tostream &os, const String &s)
        {
            return os << s.c_str();
        }

        ///////////////////////////////////////////////////////////////////////
        // String Builder
    public:
        template <typename... _P>
        static String Builder(_P &&...p)
        {
            return concatenate(default_delimiter_, std::forward<_P>(p)...);
        }

        template <typename... _P>
        static String Builder(const Char delimiter, _P &&...p)
        {
            return concatenate(delimiter, std::forward<_P>(p)...);
        }

    private:
        template <typename _T, typename... _P>
        static String concatenate(const Char delimiter, _T &&t, _P &&...p)
        {
            return toString(t) + delimiter + concatenate(delimiter, p...);
        }

        template <typename _T>
        static String concatenate(const Char, _T &&t)
        {
            return toString(t);
        }

        template <typename T>
            requires std::is_constructible_v<String, T>
        static String toString(T &&t)
        {
            return String{t};
        }

        template <typename T>
        static String toString(T &&t)
        {
            return std::format(default_placeholder_, t);
        }
        ///////////////////////////////////////////////////////////////////////
    };
}
