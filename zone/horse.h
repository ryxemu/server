#ifndef HORSES_H
#define HORSES_H

#include "npc.h"

#include <map>

class Client;
class Mob;
struct NPCType;
struct NewSpawn_Struct;

class Horse : public NPC {
   public:
	Horse(Client *owner, uint16 spell_id, const glm::vec4 &position);

	virtual void FillSpawnStruct(NewSpawn_Struct *ns, Mob *ForWho);

	static bool IsHorseSpell(uint16 spell_id);

	virtual bool IsHorse() const { return true; }

   protected:
	uint8 mount_color;
	Client *owner;

	// generate npc type records for horses
	static std::map<uint16, const NPCType *> horse_types;
	static const NPCType *GetHorseType(uint16 spell_id);
	static const NPCType *BuildHorseType(uint16 spell_id);
};

#endif
