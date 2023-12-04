#include "../common/global_define.h"
#include "zonelist.h"
#include "zoneserver.h"
#include "world_tcp_connection.h"
#include "worlddb.h"
#include "console.h"
#include "ucs.h"
#include "world_config.h"
#include "../common/servertalk.h"
#include "../common/strings.h"
#include "../common/random.h"

extern uint32			numzones;
extern bool holdzones;
extern ConsoleList		console_list;
extern UCSConnection UCSLink;
extern EQ::Random emu_random;
void CatchSignal(int sig_num);

ZSList::ZSList()
{
	NextID = 1;
	CurGroupID = 1;
	LastAllocatedPort=0;
	memset(pLockedZones, 0, sizeof(pLockedZones));
}

ZSList::~ZSList() {
}

void ZSList::ShowUpTime(WorldTCPConnection* con, const char* adminname) {
	uint32 ms = Timer::GetCurrentTime();
	std::string time_string = Strings::MillisecondsToTime(ms);
	con->SendEmoteMessage(
		adminname,
		0,
		AccountStatus::Player,
		CC_Default,
		fmt::format(
			"Worldserver Uptime | {}",
			time_string
		).c_str()
	);
}

void ZSList::Add(ZoneServer* zoneserver) {
	list.Insert(zoneserver);
	zoneserver->SendGroupIDs();	//send its initial set of group ids
}

void ZSList::KillAll() {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements()) {
		iterator.GetData()->Disconnect();
		iterator.RemoveCurrent();
		numzones--;
	}
}

void ZSList::Process() {

	if(shutdowntimer && shutdowntimer->Check()){
		Log(Logs::Detail, Logs::WorldServer, "Shutdown timer has expired. Telling all zones to shut down and exiting. (fake sigint)");
		auto pack2 = new ServerPacket;
		pack2->opcode = ServerOP_ShutdownAll;
		pack2->size=0;
		SendPacket(pack2);
		safe_delete(pack2);
		Process();
		CatchSignal(2);
	}
	if(reminder && reminder->Check() && shutdowntimer){
		SendEmoteMessage(0, 0, AccountStatus::Player, CC_Yellow , fmt::format("[SYSTEM] World coming down in {} minutes.", ((shutdowntimer->GetRemainingTime() / 1000) / 60)).c_str());
	}
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements()) {
		if (!iterator.GetData()->Process()) {
			ZoneServer* zs = iterator.GetData();
			struct in_addr in;
			in.s_addr = zs->GetIP();
			Log(Logs::Detail, Logs::WorldServer,"Removing zoneserver #%d at %s:%d",zs->GetID(),zs->GetCAddress(),zs->GetCPort());
			database.ZoneDisconnect(zs->GetZoneID());
			zs->LSShutDownUpdate(zs->GetZoneID());
			if (holdzones){
				Log(Logs::Detail, Logs::WorldServer,"Hold Zones mode is ON - rebooting lost zone");
				if(!zs->IsStaticZone())
					RebootZone(inet_ntoa(in),zs->GetCPort(),zs->GetCAddress(),zs->GetID());
				else
					RebootZone(inet_ntoa(in),zs->GetCPort(),zs->GetCAddress(),zs->GetID(),database.GetZoneID(zs->GetZoneName()));
			}

			iterator.RemoveCurrent();
			numzones--;
		}
		else {
			iterator.Advance();
		}
	}
}

bool ZSList::SendPacket(ServerPacket* pack) {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements()) {
		iterator.GetData()->SendPacket(pack);
		iterator.Advance();
	}
	return true;
}

bool ZSList::SendPacket(uint32 ZoneID, ServerPacket* pack) {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements()) {
		if (iterator.GetData()->GetZoneID() == ZoneID) {
			ZoneServer* tmp = iterator.GetData();
			return(tmp->SendPacket(pack));
		}
		iterator.Advance();
	}
	return(false);
}

ZoneServer* ZSList::FindByName(const char* zonename) {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements())
	{
		if (strcasecmp(iterator.GetData()->GetZoneName(), zonename) == 0) {
			ZoneServer* tmp = iterator.GetData();
			return tmp;
		}
		iterator.Advance();
	}
	return 0;
}

ZoneServer* ZSList::FindByID(uint32 ZoneID) {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements()) {
		if (iterator.GetData()->GetID() == ZoneID) {
			ZoneServer* tmp = iterator.GetData();
			return tmp;
		}
		iterator.Advance();
	}
	return 0;
}

ZoneServer* ZSList::FindByZoneID(uint32 ZoneID) {
	LinkedListIterator<ZoneServer*> iterator(list);
	iterator.Reset();
	while(iterator.MoreElements())
	{
		ZoneServer* tmp = iterator.GetData();
		if (tmp->GetZoneID() == ZoneID) {
			return tmp;
		}
		iterator.Advance();
	}
	return 0;
}

ZoneServer* ZSList::FindByPort(uint16 port) {
	LinkedListIterator<ZoneServer*> iterator(list);

	iterator.Reset();
	while(iterator.MoreElements())
	{
		if (iterator.GetData()->GetCPort() == port) {
			ZoneServer* tmp = iterator.GetData();
			return tmp;
		}
		iterator.Advance();
	}
	return 0;
}

bool ZSList::SetLockedZone(uint16 iZoneID, bool iLock) {
	for (auto &zone : pLockedZones) {
		if (iLock) {
			if (zone == 0) {
				zone = iZoneID;
				return true;
			}
		}
		else {
			if (zone == iZoneID) {
				zone = 0;
				return true;
			}
		}
	}
	return false;
}

bool ZSList::IsZoneLocked(uint16 iZoneID) {
	for (auto &zone : pLockedZones) {
		if (zone == iZoneID)
			return true;
	}
	return false;
}

void ZSList::ListLockedZones(const char* to, WorldTCPConnection* connection) {
	int x = 0;
	for (auto &zone : pLockedZones) {
		if (zone) {
			connection->SendEmoteMessageRaw(to, 0, AccountStatus::Player, CC_Default, database.GetZoneName(zone, true));
			x++;
		}
	}
	connection->SendEmoteMessage(to, 0, AccountStatus::Player, CC_Default, "%i zones locked.", x);
}

void ZSList::SendZoneStatus(const char* to, int16 admin, WorldTCPConnection* connection)
{

	LinkedListIterator<ZoneServer*> iterator(list, BACKWARD);
	struct in_addr in;

	iterator.Reset();
	char locked[4];
	if (WorldConfig::get()->Locked == true)
	{
		strcpy(locked, "Yes");
	}
	else
	{
		strcpy(locked, "No");
	}

	fmt::memory_buffer out;

	if (connection->IsConsole())
	{
		fmt::format_to(out, "World Locked: {}\r\n", locked);
	}
	else
	{
		fmt::format_to(out, "World Locked: {}^", locked);
	}

	if (connection->IsConsole())
	{
		fmt::format_to(out, "UCS Server: {}\r\n", UCSLink.Connected() ? "Connected" : "Unavailable");
	}
	else
	{
		fmt::format_to(out, "UCS Server: {}^", UCSLink.Connected() ? "Connected" : "Unavailable");
	}

	if (connection->IsConsole())
	{
		fmt::format_to(out, "Zoneservers online:\r\n");
	}
	else
	{
		fmt::format_to(out, "Zoneservers online:^");
	}

	int avail_zones = 0, booted_zones = 0, servers_online = 0, static_zones = 0;
	std::string buffer = " ";
	std::string is_static_string = "", zone_data_string = "";

	ZoneServer* zone_server_data = 0;

	while (iterator.MoreElements())
	{
		zone_server_data = iterator.GetData();
		in.s_addr = zone_server_data->GetIP();

		if (!zone_server_data->IsStaticZone())
		{
			is_static_string = "D";
			if (zone_server_data->GetZoneID() != 0)
			{
				++booted_zones;
			}
			else if (zone_server_data->GetZoneID() == 0 && !zone_server_data->IsBootingUp())
			{
				++avail_zones;
			}
		}
		else
		{
			is_static_string = "S";
			++static_zones;
		}

		if (zone_server_data->GetZoneID())
		{
			std::ostringstream stream;
			stream << "" << zone_server_data->GetZoneName() << " (" << zone_server_data->GetZoneID() << ")";
			zone_data_string = stream.str();
		}
		else if (zone_server_data->IsBootingUp())
		{
			zone_data_string = "BOOTING";
		}
		else
		{
			zone_data_string = "AVAILABLE";
		}

		fmt::format_to(out,
			"{} {} :: {}  :: {}:{} :: {} :: {}:{} :: {} :: ({})",
			buffer.c_str(),
			zone_server_data->GetID(),
			is_static_string.c_str(),
			inet_ntoa(in),
			zone_server_data->GetPort(),
			zone_server_data->NumPlayers(),
			zone_server_data->GetCAddress(),
			zone_server_data->GetCPort(),
			zone_data_string.c_str(),
			zone_server_data->GetZoneOSProcessID()
		);

		if (out.size() >= 3584) {
			auto output = fmt::to_string(out);
			connection->SendEmoteMessageRaw(to, 0, AccountStatus::Player, CC_NPCQuestSay, output.c_str());
			out.clear();
		}
		else
		{
			if (connection->IsConsole())
				fmt::format_to(out, "\r\n");
			else
				fmt::format_to(out, "^");
		}

		++servers_online;
		iterator.Advance();
	}

	if (connection->IsConsole())
	{
		fmt::format_to(out, "{} {} servers online.\r\n", buffer.c_str(), servers_online);
	}
	else
	{
		fmt::format_to(out, "{} {} servers online.^", buffer.c_str(), servers_online);
	}

	fmt::format_to(out, "{} {} zones are static zones, {} zones are booted zones, {} zones available.", buffer.c_str(), static_zones, booted_zones, avail_zones);

	auto output = fmt::to_string(out);
	connection->SendEmoteMessageRaw(to, 0, AccountStatus::Player, CC_NPCQuestSay, output.c_str());
}

void ZSList::SendZoneCountConsole(const char* to, int16 admin, WorldTCPConnection* connection, bool zonepop)
{

	LinkedListIterator<ZoneServer*> iterator(list, BACKWARD);

	iterator.Reset();

	fmt::memory_buffer out;
	int avail_zones = 0, booted_zones = 0, servers_online = 0, static_zones = 0, num_players = 0;
	ZoneServer* zone_server_data = 0;
	bool booted = false;

	while (iterator.MoreElements())
	{
		zone_server_data = iterator.GetData();

		if (!zone_server_data->IsStaticZone())
		{
			if (zone_server_data->GetZoneID() != 0)
			{
				++booted_zones;
				booted = true;
			}
			else if (zone_server_data->GetZoneID() == 0 && !zone_server_data->IsBootingUp())
			{
				++avail_zones;
			}
		}
		else
		{
			++static_zones;
			booted = true;
		}

		if (zonepop && booted)
		{
			fmt::format_to(out, "{}:{}\r\n", zone_server_data->GetZoneName(), zone_server_data->NumPlayers());
		}

		num_players += zone_server_data->NumPlayers();

		++servers_online;
		booted = false;
		iterator.Advance();
	}

	if (!zonepop)
	{
		fmt::format_to(out, "static:{} total:{} dyn:{} pop:{}\r\n", static_zones, servers_online, avail_zones, num_players);
	}

	auto output = fmt::to_string(out);
	connection->SendEmoteMessageRaw(to, 0, AccountStatus::Player, CC_NPCQuestSay, output.c_str());
}

void ZSList::SendChannelMessage(const char* from, const char* to, uint8 chan_num, uint8 language, uint8 lang_skill, const char* message, ...) {
	if (!message)
		return;
	va_list argptr;
	char buffer[1024];

	va_start(argptr, message);
	vsnprintf(buffer, sizeof(buffer), message, argptr);
	va_end(argptr);

	SendChannelMessageRaw(from, to, chan_num, language, lang_skill, buffer);
}

void ZSList::SendChannelMessageRaw(const char* from, const char* to, uint8 chan_num, uint8 language, uint8 lang_skill, const char* message) {
	if (!message)
		return;
	auto pack = new ServerPacket;

	pack->opcode = ServerOP_ChannelMessage;
	pack->size = sizeof(ServerChannelMessage_Struct)+strlen(message)+1;
	pack->pBuffer = new uchar[pack->size];
	memset(pack->pBuffer, 0, pack->size);
	ServerChannelMessage_Struct* scm = (ServerChannelMessage_Struct*) pack->pBuffer;
	if (from == 0) {
		strcpy(scm->from, "WServer");
	}
	else if (from[0] == 0) {
		strcpy(scm->from, "WServer");
	}
	else
		strcpy(scm->from, from);
	if (to != 0) {
		strcpy((char *) scm->to, to);
		strcpy((char *) scm->deliverto, to);
	}
	else {
		scm->to[0] = 0;
		scm->deliverto[0] = 0;
	}

	scm->language = language;
	scm->lang_skill = lang_skill;
	scm->chan_num = chan_num;
	strcpy(&scm->message[0], message);
	if (scm->chan_num == ChatChannel_OOC || scm->chan_num == ChatChannel_Broadcast || scm->chan_num == ChatChannel_GMSAY) {
		console_list.SendChannelMessage(scm);
	}
	pack->Deflate();
	SendPacket(pack);
	delete pack;
}

void ZSList::SendEmoteMessage(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message, ...) {
	if (!message)
		return;
	va_list argptr;
	char buffer[1024];

	va_start(argptr, message);
	vsnprintf(buffer, sizeof(buffer), message, argptr);
	va_end(argptr);

	SendEmoteMessageRaw(to, to_guilddbid, to_minstatus, type, buffer);
}

void ZSList::SendEmoteMessageRaw(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message) {
	if (!message)
		return;
	auto pack = new ServerPacket;

	pack->opcode = ServerOP_EmoteMessage;
	pack->size = sizeof(ServerEmoteMessage_Struct)+strlen(message)+1;
	pack->pBuffer = new uchar[pack->size];
	memset(pack->pBuffer, 0, pack->size);
	ServerEmoteMessage_Struct* sem = (ServerEmoteMessage_Struct*) pack->pBuffer;

	if (to) {
		if (to[0] == '*') {
			Console* con = console_list.FindByAccountName(&to[1]);
			if (con)
				con->SendEmoteMessageRaw(to, to_guilddbid, to_minstatus, type, message);
			delete pack;
			return;
		}
		strcpy((char *) sem->to, to);
	}
	else {
		sem->to[0] = 0;
	}

	sem->guilddbid = to_guilddbid;
	sem->minstatus = to_minstatus;
	sem->type = type;
	strcpy(&sem->message[0], message);
	char tempto[64]={0};
	if(to)
		strn0cpy(tempto,to,64);
	pack->Deflate();
	if (tempto[0] == 0) {
		SendPacket(pack);
		if (to_guilddbid == 0)
			console_list.SendEmoteMessageRaw(type, message);
	}
	else {
		ZoneServer* zs = FindByName(to);

		if (zs != 0)
			zs->SendPacket(pack);
		else
			SendPacket(pack);
	}
	delete pack;
}

void ZSList::SendTimeSync() {
	auto pack = new ServerPacket(ServerOP_SyncWorldTime, sizeof(eqTimeOfDay));
	eqTimeOfDay* tod = (eqTimeOfDay*) pack->pBuffer;
	tod->start_eqtime=worldclock.getStartEQTime();
	tod->start_realtime=worldclock.getStartRealTime();
	SendPacket(pack);
	delete pack;
}

void ZSList::NextGroupIDs(uint32 &start, uint32 &end) {
	start = CurGroupID;
	CurGroupID += 1000;	//hand them out 1000 at a time...
	if(CurGroupID < start) {	//handle overflow
		start = 1;
		CurGroupID = 1001;
	}
	end = CurGroupID - 1;
}

void ZSList::SOPZoneBootup(const char* adminname, uint32 ZoneServerID, const char* zonename, bool iMakeStatic) {
	ZoneServer* zs = 0;
	ZoneServer* zs2 = 0;
	uint32 zoneid;
	if (!(zoneid = database.GetZoneID(zonename)))
		SendEmoteMessage(adminname, 0, AccountStatus::Player, CC_Default, fmt::format("Error: SOP_ZoneBootup: zone '{}' not found in 'zone' table.", zonename).c_str());
	else {
		if (ZoneServerID != 0)
			zs = FindByID(ZoneServerID);
		else
			SendEmoteMessage(adminname, 0, AccountStatus::Player, CC_Default, "Error: SOP_ZoneBootup: ServerID must be specified");

		if (!zs)
			SendEmoteMessage(adminname, 0, AccountStatus::Player, CC_Default, "Error: SOP_ZoneBootup: zoneserver not found");
		else {
			zs2 = FindByName(zonename);
			if (zs2 != 0)
				SendEmoteMessage(adminname, 0, AccountStatus::Player, CC_Default, fmt::format("Error: SOP_ZoneBootup: zone '{}' already being hosted by ZoneServer ID {} ", zonename, zs2->GetID()).c_str());
			else {
				zs->TriggerBootup(zoneid, adminname, iMakeStatic);
				SendEmoteMessage(adminname, 0, AccountStatus::Player, CC_Default, fmt::format("Booting {} on zoneserverid {} ", zonename, ZoneServerID).c_str());
			}
		}
	}
}

void ZSList::RebootZone(const char* ip1,uint16 port,const char* ip2, uint32 skipid, uint32 zoneid){
// get random zone
	LinkedListIterator<ZoneServer*> iterator(list);
	uint32 x = 0;
	iterator.Reset();
	while(iterator.MoreElements()) {
		x++;
		iterator.Advance();
	}
	if (x == 0)
		return;
	auto tmp = new ZoneServer *[x];
	uint32 y = 0;
	iterator.Reset();
	while(iterator.MoreElements()) {
		if (!strcmp(iterator.GetData()->GetCAddress(),ip2) && !iterator.GetData()->IsBootingUp() && iterator.GetData()->GetID() != skipid) {
			tmp[y++] = iterator.GetData();
		}
		iterator.Advance();
	}
	if (y == 0) {
		safe_delete_array(tmp);
		return;
	}
	uint32 z = emu_random.Int(0, y-1);

	auto pack = new ServerPacket(ServerOP_ZoneReboot, sizeof(ServerZoneReboot_Struct));
	ServerZoneReboot_Struct* s = (ServerZoneReboot_Struct*) pack->pBuffer;
//	strcpy(s->ip1,ip1);
	strcpy(s->ip2,ip2);
	s->port = port;
	s->zoneid = zoneid;
	if(zoneid != 0)
		Log(Logs::Detail, Logs::WorldServer,"Rebooting static zone with the ID of: %i",zoneid);
	tmp[z]->SendPacket(pack);
	delete pack;
	safe_delete_array(tmp);
}

uint16	ZSList::GetAvailableZonePort()
{
	const WorldConfig *Config=WorldConfig::get();
	int i;
	uint16 port=0;

	if (LastAllocatedPort==0)
		i=Config->ZonePortLow;
	else
		i=LastAllocatedPort+1;

	while(i!=LastAllocatedPort && port==0) {
		if (i>Config->ZonePortHigh)
			i=Config->ZonePortLow;

		if (!FindByPort(i)) {
			port=i;
			break;
		}
		i++;
	}
	LastAllocatedPort=port;

	return port;
}

uint32 ZSList::GetAvailableZoneID()
{
	LinkedListIterator<ZoneServer*> iterator(list, BACKWARD);
	iterator.Reset();

	ZoneServer* zone_server_data = 0;

	while (iterator.MoreElements())
	{
		zone_server_data = iterator.GetData();

		if (zone_server_data->GetZoneID() || zone_server_data->IsBootingUp())
		{
			iterator.Advance();
		}
		else
		{
			return zone_server_data->GetID();
		}
	}

	return 0;
}

uint32 ZSList::TriggerBootup(uint32 iZoneID) {

		LinkedListIterator<ZoneServer*> iterator(list);
		iterator.Reset();
		while(iterator.MoreElements()) {
			if(iterator.GetData()->GetZoneID() == iZoneID)
			{
				return iterator.GetData()->GetID();
			}
			iterator.Advance();
		}

		iterator.Reset();
		while(iterator.MoreElements()) {
			if (iterator.GetData()->GetZoneID() == 0 && !iterator.GetData()->IsBootingUp()) {
				ZoneServer* zone=iterator.GetData();
				zone->TriggerBootup(iZoneID);
				return zone->GetID();
			}
			iterator.Advance();
		}
		return 0;

	/*Old Random boot zones use this if your server is distributed across computers.
	LinkedListIterator<ZoneServer*> iterator(list);

	srand(time(nullptr));
	uint32 x = 0;
	iterator.Reset();
	while(iterator.MoreElements()) {
		x++;
		iterator.Advance();
	}
	if (x == 0) {
		return 0;
	}

	ZoneServer** tmp = new ZoneServer*[x];
	uint32 y = 0;

	iterator.Reset();
	while(iterator.MoreElements()) {
		if (iterator.GetData()->GetZoneID() == 0 && !iterator.GetData()->IsBootingUp()) {
			tmp[y++] = iterator.GetData();
		}
		iterator.Advance();
	}
	if (y == 0) {
		safe_delete(tmp);
		return 0;
	}

	uint32 z = rand() % y;

	tmp[z]->TriggerBootup(iZoneID);
	uint32 ret = tmp[z]->GetID();
	safe_delete(tmp);
	return ret;
	*/
}

void ZSList::SendLSZones(){
	LinkedListIterator<ZoneServer*> iterator(list);
	iterator.Reset();
	while(iterator.MoreElements()) {
		ZoneServer* zs = iterator.GetData();
		zs->LSBootUpdate(zs->GetZoneID(),true);
		iterator.Advance();
	}
}

int ZSList::GetZoneCount() {
	return(numzones);
}

void ZSList::GetZoneIDList(std::vector<uint32> &zones) {
	LinkedListIterator<ZoneServer*> iterator(list);
	iterator.Reset();
	while(iterator.MoreElements()) {
		ZoneServer* zs = iterator.GetData();
		zones.push_back(zs->GetID());
		iterator.Advance();
	}
}

void ZSList::WorldShutDown(uint32 time, uint32 interval)
{
	if( time > 0 ) {
		SendEmoteMessage(0, 0, AccountStatus::Player, CC_Yellow, fmt::format("[SYSTEM] World will be shutting down in {} minutes.", (time / 60)).c_str());

		time *= 1000;
		interval *= 1000;
		if(interval < 5000) { interval = 5000; }

		shutdowntimer->Start(time);
		reminder->Start(interval - 1000);
		reminder->SetDuration(interval);
	}
	else {
		SendEmoteMessage(0, 0, AccountStatus::Player, CC_Yellow,"[SYSTEM] World is shutting down.");
		auto pack = new ServerPacket;
		pack->opcode = ServerOP_ShutdownAll;
		pack->size=0;
		SendPacket(pack);
		safe_delete(pack);
		Process();
		CatchSignal(2);
	}
}
