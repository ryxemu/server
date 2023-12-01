#ifndef LAUNCHERLIST_H_
#define LAUNCHERLIST_H_

#include "../common/types.h"
#include <map>
#include <vector>
#include <string>

class LauncherLink;
class EmuTCPConnection;
class EQLConfig;

class LauncherList {
   public:
	LauncherList();
	~LauncherList();

	void Process();

	void LoadList();
	EQLConfig *GetConfig(const char *name);
	void CreateLauncher(const char *name, uint8 dynamic_count);
	void Remove(const char *name);

	void Add(EmuTCPConnection *conn);
	LauncherLink *Get(const char *name);
	LauncherLink *FindByZone(const char *short_name);

	int GetLauncherCount();
	void GetLauncherNameList(std::vector<std::string> &list);

   protected:
	std::map<std::string, EQLConfig *> m_configs;       // we own these objects
	std::map<std::string, LauncherLink *> m_launchers;  // we own these objects
	//	std::map<std::string, EQLConfig *> m_configs;	//we own these objects
	std::vector<LauncherLink *> m_pendingLaunchers;  // we own these objects, have not yet identified themself
	int nextID;
};

#endif /*LAUNCHERLIST_H_*/
