#ifndef __RL_UTIL_H
#define __RL_UTIL_H
#include <stdint.h>

typedef uint8_t RLubyte;
typedef uint16_t RLushort;
typedef uint32_t RLuint;
typedef uint64_t RLulong;

typedef uint32_t RLint;
typedef float RLfloat;

#define RL_SUCCESS 0
#define RL_FAILURE 1
typedef uint8_t RLresult;

typedef uint8_t RLbool;

#define RL_BIN(bin) 0b##bin

#endif