#ifndef _EQE_QUESTPARSERCOLLECTION_H
#define _EQE_QUESTPARSERCOLLECTION_H

#include "../common/types.h"

#include "encounter.h"
#include "beacon.h"
#include "client.h"
#include "corpse.h"
#include "doors.h"
#include "groups.h"
#include "mob.h"
#include "object.h"
#include "raids.h"
#include "trap.h"

#include "quest_interface.h"

#include <list>
#include <map>

#define QuestFailedToLoad 0xFFFFFFFF
#define QuestUnloaded 0x00

class Client;
class Mob;
class NPC;
class QuestInterface;
namespace EQ {
class Any;
class ItemInstance;
}  // namespace EQ

class QuestParserCollection {
   public:
	QuestParserCollection();
	~QuestParserCollection();

	void RegisterQuestInterface(QuestInterface *qi, std::string ext);
	void UnRegisterQuestInterface(QuestInterface *qi, std::string ext);
	void ClearInterfaces();
	void AddVar(std::string name, std::string val);
	void Init();
	void ReloadQuests(bool reset_timers = true);
	void RemoveEncounter(const std::string name);
	QuestInterface *GetQuestInterface(uint32 id);

	bool HasQuestSub(uint32 npcid, QuestEventID evt, bool check_encounters = false);
	bool PlayerHasQuestSub(QuestEventID evt, bool check_encounters = false);
	bool SpellHasQuestSub(uint32 spell_id, QuestEventID evt, bool check_encounters = false);
	bool ItemHasQuestSub(EQ::ItemInstance *itm, QuestEventID evt, bool check_encounters = false);

	int EventNPC(QuestEventID evt, NPC *npc, Mob *init, std::string data, uint32 extra_data,
	             std::vector<std::any> *extra_pointers = nullptr);
	int EventPlayer(QuestEventID evt, Client *client, std::string data, uint32 extra_data,
	                std::vector<std::any> *extra_pointers = nullptr);
	int EventItem(QuestEventID evt, Client *client, EQ::ItemInstance *item, Mob *mob, std::string data, uint32 extra_data,
	              std::vector<std::any> *extra_pointers = nullptr);
	int EventSpell(QuestEventID evt, NPC *npc, Client *client, uint32 spell_id, uint32 extra_data,
	               std::vector<std::any> *extra_pointers = nullptr);
	int EventEncounter(QuestEventID evt, std::string encounter_name, std::string data, uint32 extra_data,
	                   std::vector<std::any> *extra_pointers = nullptr);

	void GetErrors(std::list<std::string> &quest_errors);

   private:
	bool HasQuestSubLocal(uint32 npcid, QuestEventID evt);
	bool HasQuestSubGlobal(QuestEventID evt);
	bool NPCHasEncounterSub(uint32 npc_id, QuestEventID evt);
	bool PlayerHasQuestSubLocal(QuestEventID evt);
	bool PlayerHasQuestSubGlobal(QuestEventID evt);
	bool PlayerHasEncounterSub(QuestEventID evt);
	bool SpellHasEncounterSub(uint32 spell_id, QuestEventID evt);
	bool ItemHasEncounterSub(EQ::ItemInstance *item, QuestEventID evt);
	bool HasEncounterSub(QuestEventID evt, const std::string &package_name);

	int EventNPCLocal(QuestEventID evt, NPC *npc, Mob *init, std::string data, uint32 extra_data, std::vector<std::any> *extra_pointers);
	int EventNPCGlobal(QuestEventID evt, NPC *npc, Mob *init, std::string data, uint32 extra_data, std::vector<std::any> *extra_pointers);
	int EventPlayerLocal(QuestEventID evt, Client *client, std::string data, uint32 extra_data, std::vector<std::any> *extra_pointers);
	int EventPlayerGlobal(QuestEventID evt, Client *client, std::string data, uint32 extra_data, std::vector<std::any> *extra_pointers);

	QuestInterface *GetQIByNPCQuest(uint32 npcid, std::string &filename);
	QuestInterface *GetQIByGlobalNPCQuest(std::string &filename);
	QuestInterface *GetQIByPlayerQuest(std::string &filename);
	QuestInterface *GetQIByGlobalPlayerQuest(std::string &filename);
	QuestInterface *GetQIBySpellQuest(uint32 spell_id, std::string &filename);
	QuestInterface *GetQIByItemQuest(std::string item_script, std::string &filename);
	QuestInterface *GetQIByEncounterQuest(std::string encounter_name, std::string &filename);

	int DispatchEventNPC(QuestEventID evt, NPC *npc, Mob *init, std::string data, uint32 extra_data,
	                     std::vector<std::any> *extra_pointers);
	int DispatchEventPlayer(QuestEventID evt, Client *client, std::string data, uint32 extra_data,
	                        std::vector<std::any> *extra_pointers);
	int DispatchEventItem(QuestEventID evt, Client *client, EQ::ItemInstance *item, Mob *mob, std::string data, uint32 extra_data,
	                      std::vector<std::any> *extra_pointers);
	int DispatchEventSpell(QuestEventID evt, NPC *npc, Client *client, uint32 spell_id, uint32 extra_data,
	                       std::vector<std::any> *extra_pointers);

	std::map<uint32, QuestInterface *> _interfaces;
	std::map<uint32, std::string> _extensions;
	std::list<QuestInterface *> _load_precedence;

	// 0x00 = Unloaded
	// 0xFFFFFFFF = Failed to Load
	std::map<uint32, uint32> _npc_quest_status;
	uint32 _global_npc_quest_status;
	uint32 _player_quest_status;
	uint32 _global_player_quest_status;
	std::map<uint32, uint32> _spell_quest_status;
	std::map<uint32, uint32> _item_quest_status;
	std::map<std::string, uint32> _encounter_quest_status;
};

extern QuestParserCollection *parse;

#endif
