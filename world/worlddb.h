#ifndef WORLDDB_H_
#define WORLDDB_H_

#include "../common/shareddb.h"
#include "../common/zone_numbers.h"

struct PlayerProfile_Struct;
struct CharCreate_Struct;
struct CharacterSelect_Struct;

class WorldDatabase : public SharedDatabase {
   public:
	bool GetStartZone(PlayerProfile_Struct *in_pp, CharCreate_Struct *in_cc, bool mule = false);

	void GetCharSelectInfo(uint32 account_id, CharacterSelect_Struct *, uint32 ClientVersion, uint8 &charcount, bool mule);
	int MoveCharacterToBind(int CharID, uint8 bindnum = 0);

	void SetMailKey(int CharID, int IPAddress, int MailKey);
	bool GetCharacterLevel(const char *name, int &level);

	bool LoadCharacterCreateAllocations();
	bool LoadCharacterCreateCombos();
	bool LoadSoulMarksForClient(uint32 charid, std::vector<SoulMarkEntry_Struct> &outData);
	bool GITInfo();

   protected:
};

extern WorldDatabase database;

#endif /*WORLDDB_H_*/
