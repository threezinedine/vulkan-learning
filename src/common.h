#pragma once
#include <cstdint>

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

#define ASSERT(cond)                                                                                                   \
	if (!(cond)) __debugbreak();

#define UNUSED(var) (void)(var)
