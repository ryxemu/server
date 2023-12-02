#ifndef COMMON_EMU_LIMITS_H
#define COMMON_EMU_LIMITS_H

#include "types.h"

#include <stdlib.h>


namespace EntityLimits
{
	namespace NPC {
		const int16 IINVALID = -1;
		const int16 INULL = 0;

		namespace invtype {
			const int16 TRADE_SIZE = 4;
		} // namespace invtype

	} /*NPC*/

	namespace NPCMerchant {
		const int16 IINVALID = -1;
		const int16 INULL = 0;

		namespace invtype {
			const int16 TRADE_SIZE = 4;

		} // namespace invtype

	} /*NPCMerchant*/

	namespace ClientPet {
		const int16 IINVALID = -1;
		const int16 INULL = 0;

		namespace invtype {
			const int16 TRADE_SIZE = 4;

		} // namespace invtype

	} /*Pet*/


	namespace NPCPet {
		const int16 IINVALID = -1;
		const int16 INULL = 0;

		namespace invtype {
			const int16 TRADE_SIZE = 4;

		} // namespace invtype

	} /*Pet*/

}; /*EntityLimits*/

#endif /*COMMON_EMU_LIMITS_H*/