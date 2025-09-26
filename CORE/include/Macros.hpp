// CORE/include/Macros.hpp

#pragma once

#define LOG_DEBUG(msg) Lobster::Logger::Debug({msg, \
						std::string(" (File: "), \
						std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1), \
						", Line: ",std::to_string(__LINE__),")"})

#define LOG_INFO(msg) Lobster::Logger::Info({msg, \
						std::string(" (File: "), \
						std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1), \
						", Line: ",std::to_string(__LINE__),")"})

#define LOG_WARNING(msg) Lobster::Logger::Warning({msg, \
						std::string(" (File: "), \
						std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1), \
						", Line: ",std::to_string(__LINE__),")"})

#define LOG_ERROR(msg) Lobster::Logger::Error({msg, \
						std::string(" (File: "), \
						std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1), \
						", Line: ",std::to_string(__LINE__),")"})

// Assertion handling
#define lassert(condition,message) \
    do { \
        if (!(condition)) { \
            LOG_ERROR(message); \
            __debugbreak(); \
        } \
    } while (0)

#define lassertmsg(condition,...) \
    do { \
        if (!(condition)) { \
            LOG_ERROR(__VA_ARGS__); \
            __debugbreak(); \
        } \
    } while (0)

// Force inline
#if ENGINE_COMPILER_MSVC
#define LOBSTER_FORCE_INLINE __forceinline
#else
#define LOBSTER_FORCE_INLINE __attribute__((always_inline)) inline
#endif

#ifdef _DEBUG
#define BUILD_PATH "..\\.build\\Debug\\"
#endif

#ifdef NDEBUG
#define BUILD_PATH "..\\.build\\Release\\"
#endif