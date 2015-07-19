
#ifndef COMMON_GLOBAL_DEFINES_HPP
#define COMMON_GLOBAL_DEFINES_HPP

/*
 * Microsoft ships a libc which does not provide a printing
 * mechanism for long long using the standard %lld.  Instead,
 * one has to use %I64d.  By default, we use the modifier ll.
 * Override this setting using CXXFLAGS, /DLL_FMT_STR="I64" for
 * MSVC or -DLL_FMT_STR="I64" for MinGW. We default to using ll
 * if it hasn't been set.
 */
#ifndef LL_FMT_STR
#define LL_FMT_STR "ll"
#endif

#endif // COMMON_GLOBAL_DEFINES_HPP


