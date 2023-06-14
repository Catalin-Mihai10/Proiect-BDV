#ifndef TORNADO_TYPES_HEADER
#define TORNADO_TYPES_HEADER

#include <stdint.h>

// Types defined for integers
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// Types defined for floats
typedef float d32;
typedef double d64;

// Constants for variables
const u16 MAX_LINE_SIZE = 256;
const u32 DATASET_SIZE = 67559;

#endif