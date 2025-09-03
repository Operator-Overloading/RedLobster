// CORE/include/Export.hpp

#pragma once

#ifdef LOBSTER_STATIC_DEFINE
#  define LOBSTER_API
#else
#  ifdef _WIN32
#    ifdef LOBSTER_EXPORTS
#      define LOBSTER_API __declspec(dllexport)
#    else
#      define LOBSTER_API __declspec(dllimport)
#    endif
#  else
#    define LOBSTER_API __attribute__((visibility("default")))
#  endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#  define ENGINE_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#  define ENGINE_PLATFORM_LINUX 1
#elif defined(__APPLE__)
#  define ENGINE_PLATFORM_MACOS 1
#endif

#ifdef _MSC_VER
#  define ENGINE_COMPILER_MSVC 1
#elif defined(__GNUC__)
#  define ENGINE_COMPILER_GCC 1
#elif defined(__clang__)
#  define ENGINE_COMPILER_CLANG 1
#endif