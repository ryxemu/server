#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "mob.h"
#include "../common/types.h"
#include "../common/timer.h"

class Group;
class Raid;

class Encounter : public Mob {
   public:
	Encounter(const char* enc_name);
	~Encounter();

	// abstract virtual function implementations required by base abstract class
	virtual bool Death(Mob* killerMob, int32 damage, uint16 spell_id, EQ::skills::SkillType attack_skill, uint8 killedby = 0, bool bufftic = false) { return true; }
	virtual void Damage(Mob* from, int32 damage, uint16 spell_id, EQ::skills::SkillType attack_skill, bool avoidable = true, int8 buffslot = -1, bool iBuffTic = false) { return; }
	virtual bool Attack(Mob* other, int hand = EQ::invslot::slotPrimary, int damagePct = 100) {
		return false;
	}
	virtual bool CombatRange(Mob* other, float dist_squared = 0.0f, bool check_z = false, bool pseudo_pos = false) { return false; }
	virtual bool HasRaid() { return false; }
	virtual bool HasGroup() { return false; }
	virtual Raid* GetRaid() { return 0; }
	virtual Group* GetGroup() { return 0; }

	bool IsEncounter() const { return true; }
	const char* GetEncounterName() const { return encounter_name; }

	bool Process();
	virtual void Depop(bool not_used = true) { remove_me = true; }

   protected:
	bool remove_me;
	char encounter_name[64];

   private:
};

#endif
