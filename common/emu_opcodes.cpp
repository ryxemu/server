#include "global_define.h"
#include "emu_opcodes.h"

const char *OpcodeNames[_maxEmuOpcode + 1] = {
    "OP_Unknown",

// a preprocessor hack so we dont have to maintain two lists
#define N(x) #x
#include "emu_oplist.h"
#include "chat_oplist.h"
#undef N

    ""};
