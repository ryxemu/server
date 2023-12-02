#ifndef TITLES_H
#define TITLES_H

#include <vector>

class Client;
class EQApplicationPacket;

struct TitleEntry {
	int TitleID;
	int SkillID;
	int MinSkillValue;
	int MaxSkillValue;
	int MinAAPoints;
	int MaxAAPoints;
	int Class;
	int Gender;
	int CharID;
	int Status;
	int ItemID;
	std::string Prefix;
	std::string Suffix;
	int TitleSet;
};

class TitleManager {
   public:
	TitleManager();

	bool LoadTitles();
	void ClearTitles();
	std::string GetPrefix(int TitleID);
	std::string GetSuffix(int TitleID);
	int NumberOfAvailableTitles(Client *c);
	bool IsClientEligibleForTitle(Client *c, std::vector<TitleEntry>::iterator Title);
	bool IsNewAATitleAvailable(int AAPoints, int Class);
	bool IsNewTradeSkillTitleAvailable(int SkillID, int SkillValue);
	void CreateNewPlayerTitle(Client *c, const char *Title);
	void CreateNewPlayerSuffix(Client *c, const char *Suffix);

   protected:
	std::vector<TitleEntry> Titles;
};

extern TitleManager title_manager;

#endif
