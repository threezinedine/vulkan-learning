#pragma once
#include <cstdint>
#include <cstdio>

#if defined(PLATFORM_LINUX)
#include <unistd.h>
#endif

typedef int8_t	 i8;
typedef uint8_t	 u8;
typedef int16_t	 i16;
typedef uint16_t u16;
typedef int32_t	 i32;
typedef uint32_t u32;
typedef int64_t	 i64;
typedef uint64_t u64;
typedef float	 f32;
typedef double	 f64;
typedef size_t	 usize;
typedef intptr_t isize;

#define NULLPTR			nullptr
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#ifdef PLATFORM_WINDOWS
#include <intrin.h>
#define debugbreak() __debugbreak()
#elif defined(PLATFORM_LINUX)
#include <csignal>
#define debugbreak() raise(SIGTRAP)
#endif

#define ASSERT(cond)                                                                                                   \
	do                                                                                                                 \
	{                                                                                                                  \
		if (!(cond))                                                                                                   \
		{                                                                                                              \
			debugbreak();                                                                                              \
		}                                                                                                              \
	} while (0)

#define UNUSED(var) (void)(var)

#define VK_ASSERT(exp)                                                                                                 \
	do                                                                                                                 \
	{                                                                                                                  \
		VkResult result = exp;                                                                                         \
		if (result != VK_SUCCESS)                                                                                      \
		{                                                                                                              \
			printf("Error at %s %s:%d", #exp, __FILE__, __LINE__);                                                     \
		}                                                                                                              \
	} while (0)
