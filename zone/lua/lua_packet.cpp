#include <sol/sol.hpp>

#include "../masterentity.h"
#include "lua_packet.h"

void lua_register_packet(sol::state_view &sv)
{
	auto packet = sv.new_usertype<Lua_Packet>(
	    "Packet", sol::constructors<Lua_Packet(), Lua_Packet(int, int), Lua_Packet(int, int, bool)>());
	packet["null"] = sol::readonly_property(&Lua_Packet::Null);
	packet["valid"] = sol::readonly_property(&Lua_Packet::Valid);
	packet["GetOpcode"] = &Lua_Packet::GetOpcode;
	packet["GetRawOpcode"] = &Lua_Packet::GetRawOpcode;
	packet["GetSize"] = &Lua_Packet::GetSize;
	packet["GetWritePosition"] = &Lua_Packet::GetWritePosition;
	packet["ReadDouble"] = &Lua_Packet::ReadDouble;
	packet["ReadFixedLengthString"] = &Lua_Packet::ReadFixedLengthString;
	packet["ReadFloat"] = &Lua_Packet::ReadFloat;
	packet["ReadInt16"] = &Lua_Packet::ReadInt16;
	packet["ReadInt32"] = &Lua_Packet::ReadInt32;
	packet["ReadInt64"] = &Lua_Packet::ReadInt64;
	packet["ReadInt8"] = &Lua_Packet::ReadInt8;
	packet["ReadString"] = &Lua_Packet::ReadString;
	packet["SetOpcode"] = &Lua_Packet::SetOpcode;
	packet["SetRawOpcode"] = &Lua_Packet::SetRawOpcode;
	packet["SetWritePosition"] = &Lua_Packet::SetWritePosition;
	packet["WriteDouble"] = sol::overload((void(Lua_Packet::*)(double)) & Lua_Packet::WriteDouble,
					      (void(Lua_Packet::*)(int, double)) & Lua_Packet::WriteDouble);
	packet["WriteFixedLengthString"] =
	    sol::overload((void(Lua_Packet::*)(int, std::string, int)) & Lua_Packet::WriteFixedLengthString,
			  (void(Lua_Packet::*)(std::string)) & Lua_Packet::WriteFixedLengthString);
	packet["WriteFloat"] = sol::overload((void(Lua_Packet::*)(float)) & Lua_Packet::WriteFloat,
					     (void(Lua_Packet::*)(int, float)) & Lua_Packet::WriteFloat);
	packet["WriteInt16"] = sol::overload((void(Lua_Packet::*)(int)) & Lua_Packet::WriteInt16,
					     (void(Lua_Packet::*)(int, int)) & Lua_Packet::WriteInt16);
	packet["WriteInt32"] = sol::overload((void(Lua_Packet::*)(int)) & Lua_Packet::WriteInt32,
					     (void(Lua_Packet::*)(int, int)) & Lua_Packet::WriteInt32);
	packet["WriteInt64"] = sol::overload((void(Lua_Packet::*)(int, int64)) & Lua_Packet::WriteInt64,
					     (void(Lua_Packet::*)(int64)) & Lua_Packet::WriteInt64);
	packet["WriteInt8"] = sol::overload((void(Lua_Packet::*)(int)) & Lua_Packet::WriteInt8,
					    (void(Lua_Packet::*)(int, int)) & Lua_Packet::WriteInt8);
	packet["WriteString"] = sol::overload((void(Lua_Packet::*)(int, std::string)) & Lua_Packet::WriteString,
					      (void(Lua_Packet::*)(std::string)) & Lua_Packet::WriteString);
}

//TODO: Reorder these to match emu_oplist.h again
void lua_register_packet_opcodes(sol::state_view &sv)
{
	sv.new_enum<int>("Opcode",
		{
			{ "ExploreUnknown", static_cast<int>(OP_ExploreUnknown) },
			{ "Heartbeat", static_cast<int>(OP_Heartbeat) },
			{ "ReloadUI", static_cast<int>(OP_ReloadUI) },
			{ "IncreaseStats", static_cast<int>(OP_IncreaseStats) },
			{ "ApproveZone", static_cast<int>(OP_ApproveZone) },
			{ "Dye", static_cast<int>(OP_Dye) },
			{ "Stamina", static_cast<int>(OP_Stamina) },
			{ "ControlBoat", static_cast<int>(OP_ControlBoat) },
			{ "MobUpdate", static_cast<int>(OP_MobUpdate) },
			{ "ClientUpdate", static_cast<int>(OP_ClientUpdate) },
			{ "ChannelMessage", static_cast<int>(OP_ChannelMessage) },
			{ "SimpleMessage", static_cast<int>(OP_SimpleMessage) },
			{ "FormattedMessage", static_cast<int>(OP_FormattedMessage) },
			{ "TGB", static_cast<int>(OP_TGB) },
			{ "Bind_Wound", static_cast<int>(OP_Bind_Wound) },
			{ "Charm", static_cast<int>(OP_Charm) },
			{ "Begging", static_cast<int>(OP_Begging) },
			{ "MoveCoin", static_cast<int>(OP_MoveCoin) },
			{ "SpawnDoor", static_cast<int>(OP_SpawnDoor) },
			{ "Sneak", static_cast<int>(OP_Sneak) },
			{ "ExpUpdate", static_cast<int>(OP_ExpUpdate) },
			{ "DumpName", static_cast<int>(OP_DumpName) },
			{ "RespondAA", static_cast<int>(OP_RespondAA) },
			{ "UpdateAA", static_cast<int>(OP_UpdateAA) },
			{ "SendAAStats", static_cast<int>(OP_SendAAStats) },
			{ "SendAATable", static_cast<int>(OP_SendAATable) },
			{ "AAAction", static_cast<int>(OP_AAAction) },
			{ "BoardBoat", static_cast<int>(OP_BoardBoat) },
			{ "LeaveBoat", static_cast<int>(OP_LeaveBoat) },
			{ "AdventureInfoRequest", static_cast<int>(OP_AdventureInfoRequest) },
			{ "AdventureInfo", static_cast<int>(OP_AdventureInfo) },
			{ "AdventureRequest", static_cast<int>(OP_AdventureRequest) },
			{ "AdventureDetails", static_cast<int>(OP_AdventureDetails) },
			{ "LDoNButton", static_cast<int>(OP_LDoNButton) },
			{ "AdventureData", static_cast<int>(OP_AdventureData) },
			{ "AdventureFinish", static_cast<int>(OP_AdventureFinish) },
			{ "LeaveAdventure", static_cast<int>(OP_LeaveAdventure) },
			{ "AdventureUpdate", static_cast<int>(OP_AdventureUpdate) },
			{ "SendExpZonein", static_cast<int>(OP_SendExpZonein) },
			{ "RaidUpdate", static_cast<int>(OP_RaidUpdate) },
			{ "GuildLeader", static_cast<int>(OP_GuildLeader) },
			{ "GuildPeace", static_cast<int>(OP_GuildPeace) },
			{ "GuildRemove", static_cast<int>(OP_GuildRemove) },
			{ "GuildMemberList", static_cast<int>(OP_GuildMemberList) },
			{ "GuildMemberUpdate", static_cast<int>(OP_GuildMemberUpdate) },
			{ "GuildMemberLevelUpdate", static_cast<int>(OP_GuildMemberLevelUpdate) },
			{ "GuildInvite", static_cast<int>(OP_GuildInvite) },
			{ "GuildMOTD", static_cast<int>(OP_GuildMOTD) },
			{ "SetGuildMOTD", static_cast<int>(OP_SetGuildMOTD) },
			{ "GuildPublicNote", static_cast<int>(OP_GuildPublicNote) },
			{ "GetGuildsList", static_cast<int>(OP_GetGuildsList) },
			{ "GuildDemote", static_cast<int>(OP_GuildDemote) },
			{ "GuildInviteAccept", static_cast<int>(OP_GuildInviteAccept) },
			{ "GuildWar", static_cast<int>(OP_GuildWar) },
			{ "GuildDelete", static_cast<int>(OP_GuildDelete) },
			{ "GuildManageRemove", static_cast<int>(OP_GuildManageRemove) },
			{ "GuildManageAdd", static_cast<int>(OP_GuildManageAdd) },
			{ "GuildManageStatus", static_cast<int>(OP_GuildManageStatus) },
			{ "GuildManageBanker", static_cast<int>(OP_GuildManageBanker) },
			{ "GetGuildMOTD", static_cast<int>(OP_GetGuildMOTD) },
			{ "Trader", static_cast<int>(OP_Trader) },
			{ "Bazaar", static_cast<int>(OP_Bazaar) },
			{ "BecomeTrader", static_cast<int>(OP_BecomeTrader) },
			{ "TraderItemUpdate", static_cast<int>(OP_TraderItemUpdate) },
			{ "TraderShop", static_cast<int>(OP_TraderShop) },
			{ "TraderBuy", static_cast<int>(OP_TraderBuy) },
			{ "PetCommands", static_cast<int>(OP_PetCommands) },
			{ "TradeSkillCombine", static_cast<int>(OP_TradeSkillCombine) },
			{ "AugmentItem", static_cast<int>(OP_AugmentItem) },
			{ "ItemName", static_cast<int>(OP_ItemName) },
			{ "ShopItem", static_cast<int>(OP_ShopItem) },
			{ "ShopPlayerBuy", static_cast<int>(OP_ShopPlayerBuy) },
			{ "ShopPlayerSell", static_cast<int>(OP_ShopPlayerSell) },
			{ "ShopDelItem", static_cast<int>(OP_ShopDelItem) },
			{ "ShopRequest", static_cast<int>(OP_ShopRequest) },
			{ "ShopEnd", static_cast<int>(OP_ShopEnd) },
			{ "LFGCommand", static_cast<int>(OP_LFGCommand) },
			{ "LFGAppearance", static_cast<int>(OP_LFGAppearance) },
			{ "GroupUpdate", static_cast<int>(OP_GroupUpdate) },
			{ "GroupInvite", static_cast<int>(OP_GroupInvite) },
			{ "GroupDisband", static_cast<int>(OP_GroupDisband) },
			{ "GroupInvite2", static_cast<int>(OP_GroupInvite2) },
			{ "GroupFollow", static_cast<int>(OP_GroupFollow) },
			{ "GroupFollow2", static_cast<int>(OP_GroupFollow2) },
			{ "GroupCancelInvite", static_cast<int>(OP_GroupCancelInvite) },
			{ "CustomTitles", static_cast<int>(OP_CustomTitles) },
			{ "Split", static_cast<int>(OP_Split) },
			{ "Jump", static_cast<int>(OP_Jump) },
			{ "ConsiderCorpse", static_cast<int>(OP_ConsiderCorpse) },
			{ "SkillUpdate", static_cast<int>(OP_SkillUpdate) },
			{ "GMEndTrainingResponse", static_cast<int>(OP_GMEndTrainingResponse) },
			{ "GMEndTraining", static_cast<int>(OP_GMEndTraining) },
			{ "GMTrainSkill", static_cast<int>(OP_GMTrainSkill) },
			{ "GMTraining", static_cast<int>(OP_GMTraining) },
			{ "DeleteItem", static_cast<int>(OP_DeleteItem) },
			{ "CombatAbility", static_cast<int>(OP_CombatAbility) },
			{ "TrackUnknown", static_cast<int>(OP_TrackUnknown) },
			{ "TrackTarget", static_cast<int>(OP_TrackTarget) },
			{ "Track", static_cast<int>(OP_Track) },
			{ "ItemLinkClick", static_cast<int>(OP_ItemLinkClick) },
			{ "ItemLinkResponse", static_cast<int>(OP_ItemLinkResponse) },
			{ "ItemLinkText", static_cast<int>(OP_ItemLinkText) },
			{ "RezzAnswer", static_cast<int>(OP_RezzAnswer) },
			{ "RezzComplete", static_cast<int>(OP_RezzComplete) },
			{ "SendZonepoints", static_cast<int>(OP_SendZonepoints) },
			{ "SetRunMode", static_cast<int>(OP_SetRunMode) },
			{ "InspectRequest", static_cast<int>(OP_InspectRequest) },
			{ "InspectAnswer", static_cast<int>(OP_InspectAnswer) },
			{ "SenseTraps", static_cast<int>(OP_SenseTraps) },
			{ "DisarmTraps", static_cast<int>(OP_DisarmTraps) },
			{ "Assist", static_cast<int>(OP_Assist) },
			{ "AssistGroup", static_cast<int>(OP_AssistGroup) },
			{ "PickPocket", static_cast<int>(OP_PickPocket) },
			{ "LootRequest", static_cast<int>(OP_LootRequest) },
			{ "EndLootRequest", static_cast<int>(OP_EndLootRequest) },
			{ "MoneyOnCorpse", static_cast<int>(OP_MoneyOnCorpse) },
			{ "LootComplete", static_cast<int>(OP_LootComplete) },
			{ "LootItem", static_cast<int>(OP_LootItem) },
			{ "MoveItem", static_cast<int>(OP_MoveItem) },
			{ "WhoAllRequest", static_cast<int>(OP_WhoAllRequest) },
			{ "WhoAllResponse", static_cast<int>(OP_WhoAllResponse) },
			{ "Consume", static_cast<int>(OP_Consume) },
			{ "AutoAttack", static_cast<int>(OP_AutoAttack) },
			{ "AutoAttack2", static_cast<int>(OP_AutoAttack2) },
			{ "TargetMouse", static_cast<int>(OP_TargetMouse) },
			{ "TargetCommand", static_cast<int>(OP_TargetCommand) },
			{ "TargetReject", static_cast<int>(OP_TargetReject) },
			{ "TargetHoTT", static_cast<int>(OP_TargetHoTT) },
			{ "Hide", static_cast<int>(OP_Hide) },
			{ "Forage", static_cast<int>(OP_Forage) },
			{ "Fishing", static_cast<int>(OP_Fishing) },
			{ "Bug", static_cast<int>(OP_Bug) },
			{ "Emote", static_cast<int>(OP_Emote) },
			{ "Consider", static_cast<int>(OP_Consider) },
			{ "FaceChange", static_cast<int>(OP_FaceChange) },
			{ "RandomReq", static_cast<int>(OP_RandomReq) },
			{ "RandomReply", static_cast<int>(OP_RandomReply) },
			{ "Camp", static_cast<int>(OP_Camp) },
			{ "YellForHelp", static_cast<int>(OP_YellForHelp) },
			{ "SafePoint", static_cast<int>(OP_SafePoint) },
			{ "Buff", static_cast<int>(OP_Buff) },
			{ "ColoredText", static_cast<int>(OP_ColoredText) },
			{ "SpecialMesg", static_cast<int>(OP_SpecialMesg) },
			{ "Consent", static_cast<int>(OP_Consent) },
			{ "ConsentResponse", static_cast<int>(OP_ConsentResponse) },
			{ "Stun", static_cast<int>(OP_Stun) },
			{ "BeginCast", static_cast<int>(OP_BeginCast) },
			{ "CastSpell", static_cast<int>(OP_CastSpell) },
			{ "InterruptCast", static_cast<int>(OP_InterruptCast) },
			{ "Death", static_cast<int>(OP_Death) },
			{ "FeignDeath", static_cast<int>(OP_FeignDeath) },
			{ "Illusion", static_cast<int>(OP_Illusion) },
			{ "LevelUpdate", static_cast<int>(OP_LevelUpdate) },
			{ "LevelAppearance", static_cast<int>(OP_LevelAppearance) },
			{ "MemorizeSpell", static_cast<int>(OP_MemorizeSpell) },
			{ "HPUpdate", static_cast<int>(OP_HPUpdate) },
			{ "Mend", static_cast<int>(OP_Mend) },
			{ "Taunt", static_cast<int>(OP_Taunt) },
			{ "GMDelCorpse", static_cast<int>(OP_GMDelCorpse) },
			{ "GMFind", static_cast<int>(OP_GMFind) },
			{ "GMServers", static_cast<int>(OP_GMServers) },
			{ "GMGoto", static_cast<int>(OP_GMGoto) },
			{ "GMSummon", static_cast<int>(OP_GMSummon) },
			{ "GMKill", static_cast<int>(OP_GMKill) },
			{ "GMLastName", static_cast<int>(OP_GMLastName) },
			{ "GMToggle", static_cast<int>(OP_GMToggle) },
			{ "GMEmoteZone", static_cast<int>(OP_GMEmoteZone) },
			{ "GMBecomeNPC", static_cast<int>(OP_GMBecomeNPC) },
			{ "GMHideMe", static_cast<int>(OP_GMHideMe) },
			{ "GMZoneRequest", static_cast<int>(OP_GMZoneRequest) },
			{ "GMZoneRequest2", static_cast<int>(OP_GMZoneRequest2) },
			{ "Petition", static_cast<int>(OP_Petition) },
			{ "PetitionRefresh", static_cast<int>(OP_PetitionRefresh) },
			{ "PDeletePetition", static_cast<int>(OP_PDeletePetition) },
			{ "PetitionBug", static_cast<int>(OP_PetitionBug) },
			{ "PetitionUpdate", static_cast<int>(OP_PetitionUpdate) },
			{ "PetitionCheckout", static_cast<int>(OP_PetitionCheckout) },
			{ "PetitionCheckout2", static_cast<int>(OP_PetitionCheckout2) },
			{ "PetitionDelete", static_cast<int>(OP_PetitionDelete) },
			{ "PetitionResolve", static_cast<int>(OP_PetitionResolve) },
			{ "PetitionCheckIn", static_cast<int>(OP_PetitionCheckIn) },
			{ "PetitionUnCheckout", static_cast<int>(OP_PetitionUnCheckout) },
			{ "PetitionQue", static_cast<int>(OP_PetitionQue) },
			{ "SetServerFilter", static_cast<int>(OP_SetServerFilter) },
			{ "NewSpawn", static_cast<int>(OP_NewSpawn) },
			{ "Animation", static_cast<int>(OP_Animation) },
			{ "ZoneChange", static_cast<int>(OP_ZoneChange) },
			{ "DeleteSpawn", static_cast<int>(OP_DeleteSpawn) },
			{ "EnvDamage", static_cast<int>(OP_EnvDamage) },
			{ "Action", static_cast<int>(OP_Action) },
			{ "Damage", static_cast<int>(OP_Damage) },
			{ "ManaChange", static_cast<int>(OP_ManaChange) },
			{ "ClientError", static_cast<int>(OP_ClientError) },
			{ "Save", static_cast<int>(OP_Save) },
			{ "LocInfo", static_cast<int>(OP_LocInfo) },
			{ "Surname", static_cast<int>(OP_Surname) },
			{ "ClearSurname", static_cast<int>(OP_ClearSurname) },
			{ "SwapSpell", static_cast<int>(OP_SwapSpell) },
			{ "DeleteSpell", static_cast<int>(OP_DeleteSpell) },
			{ "CloseContainer", static_cast<int>(OP_CloseContainer) },
			{ "ClickObjectAction", static_cast<int>(OP_ClickObjectAction) },
			{ "GroundSpawn", static_cast<int>(OP_GroundSpawn) },
			{ "ClearObject", static_cast<int>(OP_ClearObject) },
			{ "ZoneUnavail", static_cast<int>(OP_ZoneUnavail) },
			{ "ItemPacket", static_cast<int>(OP_ItemPacket) },
			{ "TradeRequest", static_cast<int>(OP_TradeRequest) },
			{ "TradeRequestAck", static_cast<int>(OP_TradeRequestAck) },
			{ "TradeAcceptClick", static_cast<int>(OP_TradeAcceptClick) },
			{ "TradeMoneyUpdate", static_cast<int>(OP_TradeMoneyUpdate) },
			{ "TradeCoins", static_cast<int>(OP_TradeCoins) },
			{ "CancelTrade", static_cast<int>(OP_CancelTrade) },
			{ "FinishTrade", static_cast<int>(OP_FinishTrade) },
			{ "SaveOnZoneReq", static_cast<int>(OP_SaveOnZoneReq) },
			{ "Logout", static_cast<int>(OP_Logout) },
			{ "LogoutReply", static_cast<int>(OP_LogoutReply) },
			{ "PreLogoutReply", static_cast<int>(OP_PreLogoutReply) },
			{ "DuelAccept", static_cast<int>(OP_DuelAccept) },
			{ "InstillDoubt", static_cast<int>(OP_InstillDoubt) },
			{ "SafeFallSuccess", static_cast<int>(OP_SafeFallSuccess) },
			{ "DisciplineUpdate", static_cast<int>(OP_DisciplineUpdate) },
			{ "SendGuildTributes", static_cast<int>(OP_SendGuildTributes) },
			{ "SendTributes", static_cast<int>(OP_SendTributes) },
			{ "TributeUpdate", static_cast<int>(OP_TributeUpdate) },
			{ "TributeItem", static_cast<int>(OP_TributeItem) },
			{ "TributePointUpdate", static_cast<int>(OP_TributePointUpdate) },
			{ "TributeInfo", static_cast<int>(OP_TributeInfo) },
			{ "GuildTributeInfo", static_cast<int>(OP_GuildTributeInfo) },
			{ "OpenGuildTributeMaster", static_cast<int>(OP_OpenGuildTributeMaster) },
			{ "OpenTributeMaster", static_cast<int>(OP_OpenTributeMaster) },
			{ "TributeTimer", static_cast<int>(OP_TributeTimer) },
			{ "SelectTribute", static_cast<int>(OP_SelectTribute) },
			{ "TributeNPC", static_cast<int>(OP_TributeNPC) },
			{ "TributeMoney", static_cast<int>(OP_TributeMoney) },
			{ "TributeToggle", static_cast<int>(OP_TributeToggle) },
			{ "CloseTributeMaster", static_cast<int>(OP_CloseTributeMaster) },
			{ "RecipesFavorite", static_cast<int>(OP_RecipesFavorite) },
			{ "RecipesSearch", static_cast<int>(OP_RecipesSearch) },
			{ "RecipeReply", static_cast<int>(OP_RecipeReply) },
			{ "RecipeDetails", static_cast<int>(OP_RecipeDetails) },
			{ "RecipeAutoCombine", static_cast<int>(OP_RecipeAutoCombine) },
			{ "Shielding", static_cast<int>(OP_Shielding) },
			{ "FindPersonRequest", static_cast<int>(OP_FindPersonRequest) },
			{ "FindPersonReply", static_cast<int>(OP_FindPersonReply) },
			{ "ZoneEntry", static_cast<int>(OP_ZoneEntry) },
			{ "PlayerProfile", static_cast<int>(OP_PlayerProfile) },
			{ "CharInventory", static_cast<int>(OP_CharInventory) },
			{ "ZoneSpawns", static_cast<int>(OP_ZoneSpawns) },
			{ "Weather", static_cast<int>(OP_Weather) },
			{ "ReqNewZone", static_cast<int>(OP_ReqNewZone) },
			{ "NewZone", static_cast<int>(OP_NewZone) },
			{ "ReqClientSpawn", static_cast<int>(OP_ReqClientSpawn) },
			{ "SpawnAppearance", static_cast<int>(OP_SpawnAppearance) },
			{ "ClientReady", static_cast<int>(OP_ClientReady) },
			{ "ZoneComplete", static_cast<int>(OP_ZoneComplete) },
			{ "ApproveWorld", static_cast<int>(OP_ApproveWorld) },
			{ "LogServer", static_cast<int>(OP_LogServer) },
			{ "MOTD", static_cast<int>(OP_MOTD) },
			{ "SendLoginInfo", static_cast<int>(OP_SendLoginInfo) },
			{ "DeleteCharacter", static_cast<int>(OP_DeleteCharacter) },
			{ "SendCharInfo", static_cast<int>(OP_SendCharInfo) },
			{ "ExpansionInfo", static_cast<int>(OP_ExpansionInfo) },
			{ "CharacterCreate", static_cast<int>(OP_CharacterCreate) },
			{ "CharacterCreateRequest", static_cast<int>(OP_CharacterCreateRequest) },
			{ "RandomNameGenerator", static_cast<int>(OP_RandomNameGenerator) },
			{ "GuildsList", static_cast<int>(OP_GuildsList) },
			{ "ApproveName", static_cast<int>(OP_ApproveName) },
			{ "EnterWorld", static_cast<int>(OP_EnterWorld) },
			{ "PostEnterWorld	", static_cast<int>(OP_PostEnterWorld	) },
			{ "SendSystemStats", static_cast<int>(OP_SendSystemStats) },
			{ "World_Client_CRC1", static_cast<int>(OP_World_Client_CRC1) },
			{ "World_Client_CRC2", static_cast<int>(OP_World_Client_CRC2) },
			{ "SetChatServer", static_cast<int>(OP_SetChatServer) },
			{ "SetChatServer2", static_cast<int>(OP_SetChatServer2) },
			{ "ZoneServerInfo", static_cast<int>(OP_ZoneServerInfo) },
			{ "WorldClientReady", static_cast<int>(OP_WorldClientReady) },
			{ "WorldUnknown001", static_cast<int>(OP_WorldUnknown001) },
			{ "AckPacket", static_cast<int>(OP_AckPacket) },
			{ "WearChange", static_cast<int>(OP_WearChange) },
			{ "CrashDump", static_cast<int>(OP_CrashDump) },
			{ "LoginComplete", static_cast<int>(OP_LoginComplete) },
			{ "GMNameChange", static_cast<int>(OP_GMNameChange) },
			{ "ReadBook", static_cast<int>(OP_ReadBook) },
			{ "GMKick", static_cast<int>(OP_GMKick) },
			{ "RezzRequest", static_cast<int>(OP_RezzRequest) },
			{ "MultiLineMsg", static_cast<int>(OP_MultiLineMsg) },
			{ "TimeOfDay", static_cast<int>(OP_TimeOfDay) },
			{ "CompletedTasks", static_cast<int>(OP_CompletedTasks) },
			{ "MoneyUpdate", static_cast<int>(OP_MoneyUpdate) },
			{ "ClickObject", static_cast<int>(OP_ClickObject) },
			{ "MoveDoor", static_cast<int>(OP_MoveDoor) },
			{ "TraderDelItem", static_cast<int>(OP_TraderDelItem) },
			{ "AdventureMerchantPurchase", static_cast<int>(OP_AdventureMerchantPurchase) },
			{ "TestBuff", static_cast<int>(OP_TestBuff) },
			{ "DuelDecline", static_cast<int>(OP_DuelDecline) },
			{ "RequestDuel", static_cast<int>(OP_RequestDuel) },
			{ "BazaarInspect", static_cast<int>(OP_BazaarInspect) },
			{ "ClickDoor", static_cast<int>(OP_ClickDoor) },
			{ "GroupAcknowledge", static_cast<int>(OP_GroupAcknowledge) },
			{ "GroupDelete", static_cast<int>(OP_GroupDelete) },
			{ "AdventureMerchantResponse", static_cast<int>(OP_AdventureMerchantResponse) },
			{ "ShopEndConfirm", static_cast<int>(OP_ShopEndConfirm) },
			{ "AdventureMerchantRequest", static_cast<int>(OP_AdventureMerchantRequest) },
			{ "Sound", static_cast<int>(OP_Sound) },
			{ "0x0193", static_cast<int>(OP_0x0193) },
			{ "0x0347", static_cast<int>(OP_0x0347) },
			{ "WorldComplete", static_cast<int>(OP_WorldComplete) },
			{ "MobRename", static_cast<int>(OP_MobRename) },
			{ "TaskDescription", static_cast<int>(OP_TaskDescription) },
			{ "TaskActivity", static_cast<int>(OP_TaskActivity) },
			{ "SharedTaskPlayerList", static_cast<int>(OP_SharedTaskPlayerList) },
			{ "AnnoyingZoneUnknown", static_cast<int>(OP_AnnoyingZoneUnknown) },
			{ "Some3ByteHPUpdate", static_cast<int>(OP_Some3ByteHPUpdate) },
			{ "FloatListThing", static_cast<int>(OP_FloatListThing) },
			{ "AAExpUpdate", static_cast<int>(OP_AAExpUpdate) },
			{ "ForceFindPerson", static_cast<int>(OP_ForceFindPerson) },
			{ "PlayMP3", static_cast<int>(OP_PlayMP3) },
			{ "RequestClientZoneChange", static_cast<int>(OP_RequestClientZoneChange) },
			{ "SomeItemPacketMaybe", static_cast<int>(OP_SomeItemPacketMaybe) },
			{ "QueryResponseThing", static_cast<int>(OP_QueryResponseThing) },
			{ "Some6ByteHPUpdate", static_cast<int>(OP_Some6ByteHPUpdate) },
			{ "BankerChange", static_cast<int>(OP_BankerChange) },
			{ "BecomeCorpse", static_cast<int>(OP_BecomeCorpse) },
			{ "Action2", static_cast<int>(OP_Action2) },
			{ "BazaarSearch", static_cast<int>(OP_BazaarSearch) },
			{ "SetTitle", static_cast<int>(OP_SetTitle) },
			{ "SetTitleReply", static_cast<int>(OP_SetTitleReply) },
			{ "ConfirmDelete", static_cast<int>(OP_ConfirmDelete) },
			{ "ConsentDeny", static_cast<int>(OP_ConsentDeny) },
			{ "CrystalCountUpdate", static_cast<int>(OP_CrystalCountUpdate) },
			{ "DeletePetition", static_cast<int>(OP_DeletePetition) },
			{ "DenyResponse", static_cast<int>(OP_DenyResponse) },
			{ "Disarm", static_cast<int>(OP_Disarm) },
			{ "Feedback", static_cast<int>(OP_Feedback) },
			{ "FriendsWho", static_cast<int>(OP_FriendsWho) },
			{ "GMApproval", static_cast<int>(OP_GMApproval) },
			{ "GMSearchCorpse", static_cast<int>(OP_GMSearchCorpse) },
			{ "GuildBank", static_cast<int>(OP_GuildBank) },
			{ "InitialHPUpdate", static_cast<int>(OP_InitialHPUpdate) },
			{ "InitialMobHealth", static_cast<int>(OP_InitialMobHealth) },
			{ "LFGGetMatchesRequest", static_cast<int>(OP_LFGGetMatchesRequest) },
			{ "LFGGetMatchesResponse", static_cast<int>(OP_LFGGetMatchesResponse) },
			{ "LFGResponse", static_cast<int>(OP_LFGResponse) },
			{ "LFPCommand", static_cast<int>(OP_LFPCommand) },
			{ "LFPGetMatchesRequest", static_cast<int>(OP_LFPGetMatchesRequest) },
			{ "LFPGetMatchesResponse", static_cast<int>(OP_LFPGetMatchesResponse) },
			{ "LeadershipExpToggle", static_cast<int>(OP_LeadershipExpToggle) },
			{ "LeadershipExpUpdate", static_cast<int>(OP_LeadershipExpUpdate) },
			{ "LoadSpellSet", static_cast<int>(OP_LoadSpellSet) },
			{ "LockoutTimerInfo", static_cast<int>(OP_LockoutTimerInfo) },
			{ "MendHPUpdate", static_cast<int>(OP_MendHPUpdate) },
			{ "MobHealth", static_cast<int>(OP_MobHealth) },
			{ "MoveLogDisregard", static_cast<int>(OP_MoveLogDisregard) },
			{ "MoveLogRequest", static_cast<int>(OP_MoveLogRequest) },
			{ "PetitionSearch", static_cast<int>(OP_PetitionSearch) },
			{ "PetitionSearchResults", static_cast<int>(OP_PetitionSearchResults) },
			{ "PetitionSearchText", static_cast<int>(OP_PetitionSearchText) },
			{ "RaidInvite", static_cast<int>(OP_RaidInvite) },
			{ "ReclaimCrystals", static_cast<int>(OP_ReclaimCrystals) },
			{ "Report", static_cast<int>(OP_Report) },
			{ "SenseHeading", static_cast<int>(OP_SenseHeading) },
			{ "LDoNOpen", static_cast<int>(OP_LDoNOpen) },
			{ "LDoNSenseTraps", static_cast<int>(OP_LDoNSenseTraps) },
			{ "LDoNPickLock", static_cast<int>(OP_LDoNPickLock) },
			{ "LDoNDisarmTraps", static_cast<int>(OP_LDoNDisarmTraps) },
			{ "LDoNInspect", static_cast<int>(OP_LDoNInspect) },
			{ "DynamicWall", static_cast<int>(OP_DynamicWall) },
			{ "RequestTitles", static_cast<int>(OP_RequestTitles) },
			{ "PurchaseLeadershipAA", static_cast<int>(OP_PurchaseLeadershipAA) },
			{ "UpdateLeadershipAA", static_cast<int>(OP_UpdateLeadershipAA) },
			{ "AdventurePointsUpdate", static_cast<int>(OP_AdventurePointsUpdate) },
			{ "ZoneInUnknown", static_cast<int>(OP_ZoneInUnknown) },
			{ "ZoneServerReady	", static_cast<int>(OP_ZoneServerReady	) },
			{ "ZoneGuildList", static_cast<int>(OP_ZoneGuildList) },
			{ "SendTitleList", static_cast<int>(OP_SendTitleList) },
			{ "NewTitlesAvailable", static_cast<int>(OP_NewTitlesAvailable) },
			{ "Bandolier", static_cast<int>(OP_Bandolier) },
			{ "OpenDiscordMerchant", static_cast<int>(OP_OpenDiscordMerchant) },
			{ "DiscordMerchantInventory", static_cast<int>(OP_DiscordMerchantInventory) },
			{ "GiveMoney", static_cast<int>(OP_GiveMoney) },
			{ "OnLevelMessage", static_cast<int>(OP_OnLevelMessage) },
			{ "RequestKnowledgeBase", static_cast<int>(OP_RequestKnowledgeBase) },
			{ "KnowledgeBase", static_cast<int>(OP_KnowledgeBase) },
			{ "VetRewardsAvaliable", static_cast<int>(OP_VetRewardsAvaliable) },
			{ "VetClaimRequest", static_cast<int>(OP_VetClaimRequest) },
			{ "VetClaimReply", static_cast<int>(OP_VetClaimReply) },
			{ "WeaponEquip1", static_cast<int>(OP_WeaponEquip1) },
			{ "PlayerStateAdd", static_cast<int>(OP_PlayerStateAdd) },
			{ "PlayerStateRemove", static_cast<int>(OP_PlayerStateRemove) },
			{ "WorldLogout", static_cast<int>(OP_WorldLogout) },
			{ "SessionReady", static_cast<int>(OP_SessionReady) },
			{ "Login", static_cast<int>(OP_Login) },
			{ "ServerListRequest", static_cast<int>(OP_ServerListRequest) },
			{ "PlayEverquestRequest", static_cast<int>(OP_PlayEverquestRequest) },
			{ "ChatMessage", static_cast<int>(OP_ChatMessage) },
			{ "LoginAccepted", static_cast<int>(OP_LoginAccepted) },
			{ "ServerListResponse", static_cast<int>(OP_ServerListResponse) },
			{ "Poll", static_cast<int>(OP_Poll) },
			{ "PlayEverquestResponse", static_cast<int>(OP_PlayEverquestResponse) },
			{ "EnterChat", static_cast<int>(OP_EnterChat) },
			{ "PollResponse", static_cast<int>(OP_PollResponse) },
			{ "Command", static_cast<int>(OP_Command) },
			{ "ZonePlayerToBind", static_cast<int>(OP_ZonePlayerToBind) },
			{ "AutoFire", static_cast<int>(OP_AutoFire) },
			{ "Rewind", static_cast<int>(OP_Rewind) },
			{ "TaskSelectWindow", static_cast<int>(OP_TaskSelectWindow) },
			{ "TaskActivityComplete", static_cast<int>(OP_TaskActivityComplete) },
			{ "AcceptNewTask", static_cast<int>(OP_AcceptNewTask) },
			{ "CancelTask", static_cast<int>(OP_CancelTask) },
			{ "TaskHistoryRequest", static_cast<int>(OP_TaskHistoryRequest) },
			{ "TaskHistoryReply", static_cast<int>(OP_TaskHistoryReply) },
			{ "PetBuffWindow", static_cast<int>(OP_PetBuffWindow) },
			{ "RaidJoin", static_cast<int>(OP_RaidJoin) },
			{ "Translocate", static_cast<int>(OP_Translocate) },
			{ "Sacrifice", static_cast<int>(OP_Sacrifice) },
			{ "KeyRing", static_cast<int>(OP_KeyRing) },
			{ "PopupResponse", static_cast<int>(OP_PopupResponse) },
			{ "DeleteCharge", static_cast<int>(OP_DeleteCharge) },
			{ "PotionBelt", static_cast<int>(OP_PotionBelt) },
			{ "Barter", static_cast<int>(OP_Barter) },
			{ "VoiceMacroIn", static_cast<int>(OP_VoiceMacroIn) },
			{ "VoiceMacroOut", static_cast<int>(OP_VoiceMacroOut) },
			{ "WorldObjectsSent", static_cast<int>(OP_WorldObjectsSent) },
			{ "BlockedBuffs", static_cast<int>(OP_BlockedBuffs) },
			{ "RemoveBlockedBuffs", static_cast<int>(OP_RemoveBlockedBuffs) },
			{ "ClearBlockedBuffs", static_cast<int>(OP_ClearBlockedBuffs) },
			{ "GroupUpdateLeaderAA", static_cast<int>(OP_GroupUpdateLeaderAA) },
			{ "MarkNPC", static_cast<int>(OP_MarkNPC) },
			{ "ClearNPCMarks", static_cast<int>(OP_ClearNPCMarks) },
			{ "DoGroupLeadershipAbility", static_cast<int>(OP_DoGroupLeadershipAbility) },
			{ "DelegateAbility", static_cast<int>(OP_DelegateAbility) },
			{ "SetGroupTarget", static_cast<int>(OP_SetGroupTarget) },
			{ "ApplyPoison", static_cast<int>(OP_ApplyPoison) },
			{ "FinishWindow", static_cast<int>(OP_FinishWindow) },
			{ "FinishWindow2", static_cast<int>(OP_FinishWindow2) },
			{ "ItemVerifyRequest", static_cast<int>(OP_ItemVerifyRequest) },
			{ "ItemVerifyReply", static_cast<int>(OP_ItemVerifyReply) },
			{ "GMTrainSkillConfirm", static_cast<int>(OP_GMTrainSkillConfirm) },
			{ "RestState", static_cast<int>(OP_RestState) },
			{ "AugmentInfo", static_cast<int>(OP_AugmentInfo) },
			{ "PVPStats", static_cast<int>(OP_PVPStats) },
			{ "PVPLeaderBoardRequest", static_cast<int>(OP_PVPLeaderBoardRequest) },
			{ "PVPLeaderBoardReply", static_cast<int>(OP_PVPLeaderBoardReply) },
			{ "PVPLeaderBoardDetailsRequest", static_cast<int>(OP_PVPLeaderBoardDetailsRequest) },
			{ "PVPLeaderBoardDetailsReply", static_cast<int>(OP_PVPLeaderBoardDetailsReply) },
			{ "DisciplineTimer", static_cast<int>(OP_DisciplineTimer) },
			{ "RespawnWindow", static_cast<int>(OP_RespawnWindow) },
			{ "AdventureMerchantSell", static_cast<int>(OP_AdventureMerchantSell) },
			{ "AdventureStatsRequest", static_cast<int>(OP_AdventureStatsRequest) },
			{ "AdventureStatsReply", static_cast<int>(OP_AdventureStatsReply) },
			{ "AdventureLeaderboardRequest", static_cast<int>(OP_AdventureLeaderboardRequest) },
			{ "AdventureLeaderboardReply", static_cast<int>(OP_AdventureLeaderboardReply) },
			{ "SetStartCity", static_cast<int>(OP_SetStartCity) },
			{ "LoginUnknown1", static_cast<int>(OP_LoginUnknown1) },
			{ "LoginUnknown2", static_cast<int>(OP_LoginUnknown2) },
			{ "ItemViewUnknown", static_cast<int>(OP_ItemViewUnknown) },
			{ "GetGuildMOTDReply", static_cast<int>(OP_GetGuildMOTDReply) },
			{ "SetGuildRank", static_cast<int>(OP_SetGuildRank) },
			{ "SpawnPositionUpdate", static_cast<int>(OP_SpawnPositionUpdate) },
			{ "ManaUpdate", static_cast<int>(OP_ManaUpdate) },
			{ "EnduranceUpdate", static_cast<int>(OP_EnduranceUpdate) },
			{ "MobManaUpdate", static_cast<int>(OP_MobManaUpdate) },
			{ "MobEnduranceUpdate", static_cast<int>(OP_MobEnduranceUpdate) },
			{ "GroupUpdateB", static_cast<int>(OP_GroupUpdateB) },
			{ "GroupDisbandYou", static_cast<int>(OP_GroupDisbandYou) },
			{ "GroupDisbandOther", static_cast<int>(OP_GroupDisbandOther) },
			{ "GroupLeaderChange", static_cast<int>(OP_GroupLeaderChange) },
			{ "GroupLeadershipAAUpdate", static_cast<int>(OP_GroupLeadershipAAUpdate) },
			{ "GroupRoles", static_cast<int>(OP_GroupRoles) },
			{ "SendFindableNPCs", static_cast<int>(OP_SendFindableNPCs) },
			{ "HideCorpse", static_cast<int>(OP_HideCorpse) },
			{ "TargetBuffs", static_cast<int>(OP_TargetBuffs) },
			{ "TradeBusy", static_cast<int>(OP_TradeBusy) },
			{ "GuildUpdateURLAndChannel", static_cast<int>(OP_GuildUpdateURLAndChannel) },
			{ "CameraEffect", static_cast<int>(OP_CameraEffect) },
			{ "SpellEffect", static_cast<int>(OP_SpellEffect) },
			{ "DzQuit", static_cast<int>(OP_DzQuit) },
			{ "DzListTimers", static_cast<int>(OP_DzListTimers) },
			{ "DzPlayerList", static_cast<int>(OP_DzPlayerList) },
			{ "DzAddPlayer", static_cast<int>(OP_DzAddPlayer) },
			{ "DzRemovePlayer", static_cast<int>(OP_DzRemovePlayer) },
			{ "DzSwapPlayer", static_cast<int>(OP_DzSwapPlayer) },
			{ "DzMakeLeader", static_cast<int>(OP_DzMakeLeader) },
			{ "DzExpeditionInvite", static_cast<int>(OP_DzExpeditionInvite) },
			{ "DzExpeditionInviteResponse", static_cast<int>(OP_DzExpeditionInviteResponse) },
			{ "DzExpeditionInfo", static_cast<int>(OP_DzExpeditionInfo) },
			{ "DzMemberListName", static_cast<int>(OP_DzMemberListName) },
			{ "DzMemberListStatus", static_cast<int>(OP_DzMemberListStatus) },
			{ "DzSetLeaderName", static_cast<int>(OP_DzSetLeaderName) },
			{ "DzExpeditionEndsWarning", static_cast<int>(OP_DzExpeditionEndsWarning) },
			{ "DzExpeditionLockoutTimers", static_cast<int>(OP_DzExpeditionLockoutTimers) },
			{ "DzMemberList", static_cast<int>(OP_DzMemberList) },
			{ "DzCompass", static_cast<int>(OP_DzCompass) },
			{ "DzChooseZone", static_cast<int>(OP_DzChooseZone) },
			{ "DzChooseZoneReply", static_cast<int>(OP_DzChooseZoneReply) },
			{ "BuffCreate", static_cast<int>(OP_BuffCreate) },
			{ "GuildStatus", static_cast<int>(OP_GuildStatus) },
			{ "BuffRemoveRequest", static_cast<int>(OP_BuffRemoveRequest) },
			{ "CorpseDrag", static_cast<int>(OP_CorpseDrag) },
			{ "CorpseDrop", static_cast<int>(OP_CorpseDrop) },
			{ "ChangeSize", static_cast<int>(OP_ChangeSize) },
			{ "GroupMakeLeader", static_cast<int>(OP_GroupMakeLeader) },
			{ "RemoveAllDoors", static_cast<int>(OP_RemoveAllDoors) },
			{ "RemoveNimbusEffect", static_cast<int>(OP_RemoveNimbusEffect) },
			{ "GuildCreate", static_cast<int>(OP_GuildCreate) },
			{ "AltCurrency", static_cast<int>(OP_AltCurrency) },
			{ "FellowshipUpdate", static_cast<int>(OP_FellowshipUpdate) },
			{ "AltCurrencyMerchantRequest", static_cast<int>(OP_AltCurrencyMerchantRequest) },
			{ "AltCurrencyMerchantReply", static_cast<int>(OP_AltCurrencyMerchantReply) },
			{ "AltCurrencyPurchase", static_cast<int>(OP_AltCurrencyPurchase) },
			{ "AltCurrencySellSelection", static_cast<int>(OP_AltCurrencySellSelection) },
			{ "AltCurrencyReclaim", static_cast<int>(OP_AltCurrencyReclaim) },
			{ "AltCurrencySell", static_cast<int>(OP_AltCurrencySell) },
			{ "Untargetable", static_cast<int>(OP_Untargetable) },
			{ "CrystalReclaim", static_cast<int>(OP_CrystalReclaim) },
			{ "CrystalCreate", static_cast<int>(OP_CrystalCreate) },
			{ "SendMaxCharacters", static_cast<int>(OP_SendMaxCharacters) },
			{ "SendMembership", static_cast<int>(OP_SendMembership) },
			{ "SendMembershipDetails", static_cast<int>(OP_SendMembershipDetails) },
			{ "LFGuild", static_cast<int>(OP_LFGuild) },
			{ "XTargetRequest", static_cast<int>(OP_XTargetRequest) },
			{ "XTargetResponse", static_cast<int>(OP_XTargetResponse) },
			{ "XTargetAutoAddHaters", static_cast<int>(OP_XTargetAutoAddHaters) },
			{ "Weblink", static_cast<int>(OP_Weblink) },
			{ "InspectMessageUpdate", static_cast<int>(OP_InspectMessageUpdate) },
			{ "ItemPreview", static_cast<int>(OP_ItemPreview) },
			{ "MercenaryDataRequest", static_cast<int>(OP_MercenaryDataRequest) },
			{ "MercenaryDataResponse", static_cast<int>(OP_MercenaryDataResponse) },
			{ "MercenaryHire", static_cast<int>(OP_MercenaryHire) },
			{ "MercenaryUnknown1", static_cast<int>(OP_MercenaryUnknown1) },
			{ "MercenaryTimer", static_cast<int>(OP_MercenaryTimer) },
			{ "MercenaryAssign", static_cast<int>(OP_MercenaryAssign) },
			{ "MercenaryDataUpdate", static_cast<int>(OP_MercenaryDataUpdate) },
			{ "MercenaryCommand", static_cast<int>(OP_MercenaryCommand) },
			{ "MercenarySuspendRequest", static_cast<int>(OP_MercenarySuspendRequest) },
			{ "MercenarySuspendResponse", static_cast<int>(OP_MercenarySuspendResponse) },
			{ "MercenaryUnsuspendResponse", static_cast<int>(OP_MercenaryUnsuspendResponse) },
			{ "MercenaryDataUpdateRequest", static_cast<int>(OP_MercenaryDataUpdateRequest) },
			{ "MercenaryDismiss", static_cast<int>(OP_MercenaryDismiss) },
			{ "MercenaryTimerRequest", static_cast<int>(OP_MercenaryTimerRequest) },
			{ "OpenInventory", static_cast<int>(OP_OpenInventory) },
			{ "OpenContainer", static_cast<int>(OP_OpenContainer) },
			{ "Marquee", static_cast<int>(OP_Marquee) },
			{ "ClientTimeStamp", static_cast<int>(OP_ClientTimeStamp) },
			{ "GuildPromote", static_cast<int>(OP_GuildPromote) },
			{ "Fling", static_cast<int>(OP_Fling) }
		}
	);
}