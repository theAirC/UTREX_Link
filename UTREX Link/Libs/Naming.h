#pragma once

#include <stdint.h>

#define _JOIN(x,y) x##y
#define JOIN(x,y)  _JOIN(x,y)

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8 byte;

#define MSb(x)      (byte)((x) & ~(~0 >> 1))
#define LSb(x)      (byte)((x) & 1)

#define MASK(x)     (~((x) - 1))
#define SBI(r,b)    (r |=  (1 << (b)))
#define CBI(r,b)    (r &= ~(1 << (b)))
#define VAL(r,b)    (r &   (1 << (b)))

#define Jk(r,J,k)   r = ( ((J) & ~(r)) | ((k) & (r)) )

#define asize(x)    (sizeof(x)/sizeof(x[0]))

#define _fill(array, item) for(byte i = 0; i < asize(array); i++) array[i] = item;
#define _store(reg, array) for(byte i = 0; i < asize(array); i++) item = array[i];
