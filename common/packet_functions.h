#ifndef PACKET_FUNCTIONS_H
#define PACKET_FUNCTIONS_H
#include "types.h"

class EQApplicationPacket;

uint32 roll(uint32 in, uint8 bits);
uint64 roll(uint64 in, uint8 bits);
uint32 rorl(uint32 in, uint8 bits);
uint64 rorl(uint64 in, uint8 bits);

void EncryptProfilePacket(EQApplicationPacket* app);
void EncryptProfilePacket(uchar* pBuffer, uint32 size);

void EncryptSpawnPacket(EQApplicationPacket* app);
void EncryptSpawnPacket(uchar* pBuffer, uint32 size);

void EncryptZoneSpawnPacket(EQApplicationPacket* app);
void EncryptZoneSpawnPacket(uchar* pBuffer, uint32 size);

uint32 EstimateDeflateBuffer(uint32 len);
int DeflatePacket(const unsigned char* in_data, int in_length, unsigned char* out_data, int max_out_length);
uint32 InflatePacket(const uchar* indata, uint32 indatalen, uchar* outdata, uint32 outdatalen, bool iQuiet = false);
uint32 GenerateCRC(uint32 b, uint32 bufsize, uchar* buf);

#endif
