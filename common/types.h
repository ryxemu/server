#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
typedef uint8_t byte;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#ifdef _WINDOWS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifndef __cplusplus
typedef enum { true,
	           false } bool;
#endif

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef const char Const_char;  // for perl XS

#ifdef _WINDOWS
#if (!defined(_MSC_VER) || (defined(_MSC_VER) && _MSC_VER < 1900))
#define snprintf _snprintf
#endif
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
typedef void ThreadReturnType;
#define THREAD_RETURN(x) \
	_endthread();        \
	return;
#else
typedef void* ThreadReturnType;
#define THREAD_RETURN(x) return (x);
#endif

#define safe_delete(d) \
	if (d) {           \
		delete d;      \
		d = nullptr;   \
	}
#define safe_delete_array(d) \
	if (d) {                 \
		delete[] d;          \
		d = nullptr;         \
	}
#define L32(i) ((uint32)i)
#define H32(i) ((uint32)(i >> 32))
#define L16(i) ((uint16)i)

#ifndef WIN32
// More WIN32 compatability
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef char CHAR;
typedef unsigned short WORD;
typedef float FLOAT;
typedef FLOAT *PFLOAT;
typedef BYTE *PBYTE, *LPBYTE;
typedef int *PINT, *LPINT;
typedef WORD *PWORD, *LPWORD;
typedef long *LPLONG, LONG;
typedef DWORD *PDWORD, *LPDWORD;
typedef int INT;
typedef unsigned int UINT, *PUINT, *LPUINT;
#endif

#ifdef _WINDOWS
#define DLLFUNC extern "C" __declspec(dllexport)
#else
#define DLLFUNC extern "C"
#endif

// htonll and ntohll already defined on windows
#ifndef WIN32
#if defined(__linux__)
#include <endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__)
#include <sys/endian.h>
#elif defined(__OpenBSD__)
#include <sys/types.h>
#define be16toh(x) betoh16(x)
#define be32toh(x) betoh32(x)
#define be64toh(x) betoh64(x)
#endif
#define htonll(x) htobe64(x)
#define ntohll(x) be64toh(x)
#endif

#endif
