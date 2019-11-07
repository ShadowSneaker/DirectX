#pragma once


#define ASSERT static_assert
#define INLINE __forceinline

#define DEPRECATED(Message) [[deprecated(Message)]]


#define MICRO_NUMBER (1.e-8f)
#define SMALL_NUMBER (1.e-4f)
#define LARGE_NUMBER (3.4e+38f)

#define RETURN(x) return x;



typedef unsigned int uint;

typedef bool Byte;
typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

