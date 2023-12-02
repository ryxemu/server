#include "../common/database.h"
#include "../common/guilds.h"
#include "../common/strings.h"

#include "guild_mgr.h"
#include "worldserver.h"

extern WorldServer worldserver;

void Client::SendGuildMOTD(bool GetGuildMOTDReply) {
	auto outapp = new EQApplicationPacket(OP_GuildMOTD, sizeof(GuildMOTD_Struct));

	// When the Client gets an OP_GuildMOTD, it compares the text to the version it has previously stored.
	// If the text in the OP_GuildMOTD packet is the same, it does nothing. If not the same, it displays
	// the new MOTD and then stores the new text.
	//

	GuildMOTD_Struct *motd = (GuildMOTD_Struct *)outapp->pBuffer;
	motd->unknown64 = 0;
	strn0cpy(motd->name, m_pp.name, 64);

	if (IsInAGuild()) {
		if (!guild_mgr.GetGuildMOTD(GuildID(), motd->motd, motd->name)) {
			motd->name[0] = '\0';
			strcpy(motd->motd, "ERROR GETTING MOTD!");
		}
	} else {
		// we have to send them an empty MOTD anywyas.
		motd->motd[0] = '\0';  // just to be sure
		motd->name[0] = '\0';  // just to be sure
	}

	Log(Logs::Detail, Logs::Guilds, "Sending OP_GuildMOTD of length %d", outapp->size);

	FastQueuePacket(&outapp);
}

void Client::SendGuildSpawnAppearance() {
	if (!IsInAGuild()) {
		// clear guildtag
		SendAppearancePacket(AT_GuildID, GUILD_NONE);
		Log(Logs::Detail, Logs::Guilds, "Sending spawn appearance for no guild tag.");
	} else {
		uint8 rank = guild_mgr.GetDisplayedRank(GuildID(), GuildRank(), CharacterID());
		Log(Logs::Detail, Logs::Guilds, "Sending spawn appearance for guild %d at rank %d", GuildID(), rank);
		SendAppearancePacket(AT_GuildID, GuildID());
		SendAppearancePacket(AT_GuildRank, rank);
	}
	UpdateWho();
}

void Client::SendGuildList() {
	auto outapp = new EQApplicationPacket(OP_GuildsList);

	// ask the guild manager to build us a nice guild list packet
	outapp->pBuffer = guild_mgr.MakeOldGuildList(outapp->size);

	if (outapp->pBuffer == nullptr) {
		Log(Logs::Detail, Logs::Guilds, "Unable to make guild list!");
		safe_delete(outapp);
		return;
	}

	Log(Logs::Detail, Logs::Guilds, "Sending OP_GuildsList of length %d", outapp->size);

	FastQueuePacket(&outapp);
}

void Client::SendPlayerGuild() {
	auto outapp = new EQApplicationPacket(OP_GuildAdded, sizeof(GuildUpdate_Struct));
	GuildUpdate_Struct *gu = (GuildUpdate_Struct *)outapp->pBuffer;

	int16 guid = this->GuildID();
	std::string tmp;

	if (guild_mgr.GetGuildNameByID(guid, tmp)) {
		Log(Logs::Detail, Logs::Guilds, "SendPlayerGuild(): GUID: %d Name: %s", guid, tmp.c_str());
		gu->guildID = guid;
		memcpy(gu->entry.name, tmp.c_str(), 64);
		gu->entry.guildID = guid;
		gu->entry.exists = 1;
	} else {
		gu->entry.guildID = 0xFFFFFFFF;
		gu->entry.exists = 0;
	}

	gu->entry.unknown1 = 0xFFFFFFFF;
	gu->entry.unknown3 = 0xFFFFFFFF;

	Log(Logs::Detail, Logs::Guilds, "Sending OP_GuildAdded of length %d guildID %d", outapp->size, gu->entry.guildID);

	FastQueuePacket(&outapp);
}

void Client::RefreshGuildInfo() {
	uint32 OldGuildID = guild_id;

	guildrank = GUILD_RANK_NONE;
	guild_id = GUILD_NONE;

	CharGuildInfo info;
	if (!guild_mgr.GetCharInfo(CharacterID(), info)) {
		Log(Logs::Detail, Logs::Guilds, "Unable to obtain guild char info for %s (%d)", GetName(), CharacterID());
		return;
	}

	guildrank = info.rank;
	guild_id = info.guild_id;

	SendGuildSpawnAppearance();
}

void EntityList::SendGuildMOTD(uint32 guild_id) {
	if (guild_id == GUILD_NONE)
		return;
	auto it = client_list.begin();
	while (it != client_list.end()) {
		Client *client = it->second;
		if (client->GuildID() == guild_id) {
			client->SendGuildMOTD();
		}
		++it;
	}
}

void EntityList::SendGuildSpawnAppearance(uint32 guild_id) {
	if (guild_id == GUILD_NONE)
		return;
	auto it = client_list.begin();
	while (it != client_list.end()) {
		Client *client = it->second;
		if (client->GuildID() == guild_id) {
			client->SendGuildSpawnAppearance();
		}
		++it;
	}
}

void EntityList::RefreshAllGuildInfo(uint32 guild_id) {
	if (guild_id == GUILD_NONE)
		return;
	auto it = client_list.begin();
	while (it != client_list.end()) {
		Client *client = it->second;
		if (client->GuildID() == guild_id) {
			client->RefreshGuildInfo();
		}
		++it;
	}
}

void EntityList::SendGuildList() {
	auto it = client_list.begin();
	while (it != client_list.end()) {
		Client *client = it->second;
		client->SendGuildList();
		++it;
	}
}
