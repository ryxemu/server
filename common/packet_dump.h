#ifndef PACKET_DUMP_H
#define PACKET_DUMP_H

#include "../common/types.h"

class ServerPacket;

void DumpPacketAscii(const uchar* buf, uint32 size, uint32 cols = 16, uint32 skip = 0);
void DumpPacketHex(const uchar* buf, uint32 size, uint32 cols = 16, uint32 skip = 0);
std::string DumpPacketHexToString(const uchar* buf, uint32 size, uint32 cols = 16, uint32 skip = 0);
std::string DumpPacketToRawString(const uchar* buf, uint32 size);
void DumpPacketBin(const void* data, uint32 len);
void DumpPacket(const uchar* buf, uint32 size);
void DumpPacket(const ServerPacket* pack, bool iShowInfo = false);
void DumpPacketBin(const ServerPacket* pack);
void DumpPacketBin(uint32 data);
void DumpPacketBin(uint16 data);
void DumpPacketBin(uint8 data);
std::string DumpServerPacketToString(const ServerPacket* pack);

#endif
