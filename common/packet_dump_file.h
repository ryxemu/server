#ifndef PACKET_DUMP_FILE_H
#define PACKET_DUMP_FILE_H

#include <iostream>

#include "../common/types.h"

class EQApplicationPacket;

void FileDumpPacketAscii(const char* filename, const uchar* buf, uint32 size, uint32 cols = 16, uint32 skip = 0);
void FileDumpPacketHex(const char* filename, const uchar* buf, uint32 size, uint32 cols = 16, uint32 skip = 0);
void FileDumpPacketHex(const char* filename, const EQApplicationPacket* app);
void FileDumpPacketAscii(const char* filename, const EQApplicationPacket* app);
void FileDumpPacket(const char* filename, const uchar* buf, uint32 size);
void FileDumpPacket(const char* filename, const EQApplicationPacket* app);
void FilePrintLine(const char* filename, bool prefix_timestamp = false, const char* text = 0, ...);
void FilePrint(const char* filename, bool newline = true, bool prefix_timestamp = false, const char* text = 0, ...);
#endif
