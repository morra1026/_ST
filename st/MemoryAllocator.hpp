#include "st/String.hpp"

namespace st
{
    template <class _Ty>
    class MemoryAllocator
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        // c++ Named Requirements : Allocator
        using value_type = _Ty;

        MemoryAllocator() = default;

        template <class _U>
        constexpr MemoryAllocator(const MemoryAllocator<_U> &) noexcept {};

        void deallocate(_Ty *p, size_t n)
        {
            tcout << __FUNCTION__ << _T(" n : ") << n << _T(" p : ")<< p << tendl;
            free(p);
        };

        value_type *allocate(size_t n)
        {
            auto p = (value_type *)malloc(sizeof(value_type) * n);
            tcout << __FUNCTION__ << _T(" n : ") << n << _T(" p : ")<< p << tendl;
            return p;
        };
        ///////////////////////////////////////////////////////////////////////////////
    };

    // template<class _T, class _U>
    // bool operator==(const MemoryAllocator<_T>&, const MemoryAllocator<_U>&) { return true; }

    // template<class _T, class _U>
    // bool operator!=(const MemoryAllocator<_T>& t, const MemoryAllocator<_U>& u) { return !(t == u); }

}