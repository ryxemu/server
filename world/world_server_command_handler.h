#include "iostream"
#include "../common/cli/eqemu_command_handler.h"

#ifndef EQEMU_WORLD_SERVER_COMMAND_HANDLER_H
#define EQEMU_WORLD_SERVER_COMMAND_HANDLER_H

namespace WorldserverCommandHandler {
void CommandHandler(int argc, char **argv);
void Version(int argc, char **argv, argh::parser &cmd, std::string &description);
void DatabaseVersion(int argc, char **argv, argh::parser &cmd, std::string &description);
void DatabaseGetSchema(int argc, char **argv, argh::parser &cmd, std::string &description);
void DatabaseDump(int argc, char **argv, argh::parser &cmd, std::string &description);
};  // namespace WorldserverCommandHandler

#endif  // EQEMU_WORLD_SERVER_COMMAND_HANDLER_H