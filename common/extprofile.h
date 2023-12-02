#ifndef EXTENDED_PROFILE_H
#define EXTENDED_PROFILE_H

#include "eq_packet_structs.h"
#include "inventory_profile.h"

#pragma pack(1)

/*
    This is a place to store data that dosent have a home in the
    official player profile.

    Try not to expand or re-arrange thing in this struct
    to make conversion between sizes easier.
    if something gets removed from here, just turn it into an unused
    item, so conversion is not needed. Then reuse old unused values if
    possible later instead of adding more, so long as old values left
    over would not be extrememly unpleasent side effects.
*/
struct ExtendedProfile_Struct {
	// Pet stuff
	uint16 pet_id;                          /* Not Used */
	uint16 old_pet_hp;                      /* Not Used */
	uint16 old_pet_mana;                    /* Not Used */
	SpellBuff_Struct pet_buffs[BUFF_COUNT]; /* Not Used */
	EQ::TextureProfile pet_items;           /* Not Used */
	char merc_name[64];                     /* Used */

	uint32 aa_effects;         /* Used */
	uint32 perAA;              /* Used: % of exp going to AAs */
	uint32 expended_aa;        /* Used: Total of expended AA */
	uint32 pet_hp;             /* Not Used */
	uint32 pet_mana;           /* Not Used */
	uint32 mercTemplateID;     /* Not Used */
	uint32 mercSuspendedTime;  /* Not Used */
	bool mercIsSuspended;      /* Not Used */
	uint32 mercTimerRemaining; /* Not Used */
	uint8 mercGender;          /* Not Used */
	int32 mercState;           /* Not Used */
};

#pragma pack()

void InitExtendedProfile(ExtendedProfile_Struct *p);
bool SetExtendedProfile(ExtendedProfile_Struct *to, char *old, unsigned int len);

#endif
