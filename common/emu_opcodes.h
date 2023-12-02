#ifndef EMU_OPCODES_H
#define EMU_OPCODES_H

// this is the highest opcode possibly used in the regular EQ protocol
#define MAX_EQ_OPCODE 0xFFFF

/*


the list of opcodes is in emu_oplist.h

we somewhat rely on the fact that we have more than 255 opcodes,
so we know the enum type for the opcode defines must be at least
16 bits, so we can use the protocol flags on them.

*/

typedef enum {  // EQEmu internal opcodes list
	OP_Unknown = 0,

// a preprocessor hack so we dont have to maintain two lists
#define N(x) x
#include "emu_oplist.h"
#include "chat_oplist.h"
#undef N

	_maxEmuOpcode
} EmuOpcode;

extern const char *OpcodeNames[_maxEmuOpcode + 1];

#endif
