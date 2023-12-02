#ifndef GUILD_H
#define GUILD_H

#include "types.h"

#define GUILD_NONE 0xFFFFFFFF  // user has no guild

#define GUILD_MAX_RANK 8  // 0-2 - some places in the code assume a single digit, dont go above 9

// defines for standard ranks
#define GUILD_MEMBER 0
#define GUILD_OFFICER 1
#define GUILD_LEADER 2
#define GUILD_RANK_NONE (GUILD_MAX_RANK + 1)

typedef enum {
	GUILD_HEAR = 0,
	GUILD_SPEAK = 1,
	GUILD_INVITE = 2,
	GUILD_REMOVE = 3,
	GUILD_PROMOTE = 4,
	GUILD_DEMOTE = 5,
	GUILD_MOTD = 6,
	GUILD_WARPEACE = 7,
	_MaxGuildAction
} GuildAction;

#endif
