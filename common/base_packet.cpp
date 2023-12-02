#include "global_define.h"
#include "base_packet.h"
#include "misc.h"
#include "packet_dump.h"

BasePacket::BasePacket(const unsigned char *buf, uint32 len) {
	this->pBuffer = nullptr;
	this->size = 0;
	this->_wpos = 0;
	this->_rpos = 0;
	this->timestamp.tv_sec = 0;
	if (len > 0) {
		this->size = len;
		pBuffer = new unsigned char[len];
		if (buf) {
			memcpy(this->pBuffer, buf, len);
		} else {
			memset(this->pBuffer, 0, len);
		}
	}
}

BasePacket::~BasePacket() {
	if (pBuffer)
		delete[] pBuffer;
	pBuffer = nullptr;
}

void BasePacket::build_raw_header_dump(char *buffer, uint16 seq) const {
	if (timestamp.tv_sec) {
		char temp[20];
		strftime(temp, 20, "%F %T", localtime((const time_t *)&timestamp.tv_sec));
		buffer += sprintf(buffer, "%s.%06lu ", temp, timestamp.tv_usec);
	}
	if (src_ip) {
		std::string sIP, dIP;
		sIP = long2ip(src_ip);
		dIP = long2ip(dst_ip);
		buffer += sprintf(buffer, "[%s:%d->%s:%d]\n", sIP.c_str(), src_port, dIP.c_str(), dst_port);
	}
	if (seq != 0xffff)
		buffer += sprintf(buffer, "[Seq=%u] ", seq);
}

void BasePacket::DumpRawHeader(uint16 seq, FILE *to) const {
	char buff[128];
	build_raw_header_dump(buff, seq);
	fprintf(to, "%s", buff);
}

void BasePacket::build_header_dump(char *buffer) const {
	sprintf(buffer, "[packet]\n");
}

void BasePacket::DumpRawHeaderNoTime(uint16 seq, FILE *to) const {
	if (src_ip) {
		std::string sIP, dIP;
		sIP = long2ip(src_ip);
		dIP = long2ip(dst_ip);
		fprintf(to, "[%s:%d->%s:%d] ", sIP.c_str(), src_port, dIP.c_str(), dst_port);
	}
	if (seq != 0xffff)
		fprintf(to, "[Seq=%u] ", seq);
}

void BasePacket::DumpRaw(FILE *to) const {
	DumpRawHeader();
	if (pBuffer && size)
		dump_message_column(pBuffer, size, " ", to);
	fprintf(to, "\n");
}

void BasePacket::ReadString(char *str, uint32 Offset, uint32 MaxLength) const {
	uint32 i = 0, j = Offset;

	do {
		str[i++] = pBuffer[j++];
	} while ((j < size) && (i < MaxLength) && (str[i - 1] != 0));

	str[i - 1] = '\0';
}

void DumpPacketHex(const BasePacket *app) {
	DumpPacketHex(app->pBuffer, app->size);
}

void DumpPacketAscii(const BasePacket *app) {
	DumpPacketAscii(app->pBuffer, app->size);
}

void DumpPacketBin(const BasePacket *app) {
	DumpPacketBin(app->pBuffer, app->size);
}
