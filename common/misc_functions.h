#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include "types.h"
#include <string>
#include <time.h>

#ifndef ERRBUF_SIZE
#define ERRBUF_SIZE 1024
#endif

// These are helper macros for dealing with packets of variable length, typically those that contain
// variable length strings where it is not convenient to use a fixed length struct.
//
#define VARSTRUCT_DECODE_TYPE(Type, Buffer) \
	*(Type*)Buffer;                         \
	Buffer += sizeof(Type);
#define VARSTRUCT_DECODE_STRING(String, Buffer) \
	strcpy(String, Buffer);                     \
	Buffer += strlen(String) + 1;
#define VARSTRUCT_ENCODE_STRING(Buffer, String)     \
	{                                               \
		int length = sprintf(Buffer, "%s", String); \
		Buffer += length + 1;                       \
	}
#define VARSTRUCT_ENCODE_INTSTRING(Buffer, Number)  \
	{                                               \
		int length = sprintf(Buffer, "%i", Number); \
		Buffer += length + 1;                       \
	}
#define VARSTRUCT_ENCODE_TYPE(Type, Buffer, Value) \
	{                                              \
		*(Type*)Buffer = Value;                    \
		Buffer += sizeof(Type);                    \
	}
#define VARSTRUCT_SKIP_TYPE(Type, Buffer) Buffer += sizeof(Type);

#define VERIFY_PACKET_LENGTH(OPCode, Packet, StructName)                                                                       \
	if (Packet->size != sizeof(StructName)) {                                                                                  \
		Log(Logs::Detail, Logs::Netcode, "Size mismatch in " #OPCode " expected %i got %i", sizeof(StructName), Packet->size); \
		DumpPacket(Packet);                                                                                                    \
		return;                                                                                                                \
	}

int32 filesize(FILE* fp);
uint32 ResolveIP(const char* hostname, char* errbuf = 0);
bool ParseAddress(const char* iAddress, uint32* oIP, uint16* oPort, char* errbuf = 0);
void CoutTimestamp(bool ms = true);
float EQ13toFloat(int d);
float NewEQ13toFloat(int d);
float EQ19toFloat(int d);
float EQHtoFloat(int d);
int FloatToEQ13(float d);
int NewFloatToEQ13(float d);
int FloatToEQ19(float d);
int FloatToEQH(float d);
uint32 SwapBits21And22(uint32 mask);
uint32 Catch22(uint32 mask);

// macro to catch fp errors (provided by noudness)
#define FCMP(a, b) (fabs(a - b) < FLT_EPSILON)

#define _ITOA_BUFLEN 25
const char* itoa(int num);  // not thread safe
#ifndef _WINDOWS
const char* itoa(int num, char* a, int b);
#endif

class InitWinsock {
   public:
	InitWinsock();
	~InitWinsock();
};

float FixHeading(float in);

#endif
