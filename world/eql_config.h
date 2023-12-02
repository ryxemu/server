#ifndef EQLCONFIG_H_
#define EQLCONFIG_H_

#include "../common/types.h"
#include "worlddb.h"
#include <map>
#include <string>

class LauncherLink;

typedef struct {
	std::string name;
	uint16 port;
} LauncherZone;

// a class exported to perl representing a launcher's in-DB config
class EQLConfig {
   public:
	EQLConfig(const char *launcher_name);

	void LoadSettings();
	static EQLConfig *CreateLauncher(const char *name, uint8 dynamic_count);

	void GetZones(std::vector<LauncherZone> &result);

	// BEGIN PERL EXPORT
	Const_char *GetName() const { return (m_name.c_str()); }
	int GetStaticCount() const { return (m_zones.size()); }
	bool IsConnected() const;  // is this launcher connected to world

	void DeleteLauncher();  // kill this launcher and all its zones.

	void RestartZone(Const_char *zone_ref);
	void StopZone(Const_char *zone_ref);
	void StartZone(Const_char *zone_ref);

	bool BootStaticZone(Const_char *short_name, uint16 port);
	bool ChangeStaticZone(Const_char *short_name, uint16 port);
	bool DeleteStaticZone(Const_char *short_name);

	bool SetDynamicCount(int count);
	int GetDynamicCount() const;

	std::vector<std::string> ListZones();  // returns an array of zone refs
	std::map<std::string, std::string> GetZoneDetails(Const_char *zone_ref);
	// END PERL EXPORT

   protected:
	const std::string m_name;

	uint8 m_dynamics;

	std::map<std::string, LauncherZone> m_zones;  // static zones.
};

#endif /*EQLCONFIG_H_*/
