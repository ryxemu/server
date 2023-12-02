#ifndef EQEMU_EQEMU_COMMAND_HANDLER_H
#define EQEMU_EQEMU_COMMAND_HANDLER_H

#include "argh.h"
#include "terminal_color.hpp"

namespace EQEmuCommand {

extern std::map<std::string, void (*)(
                                 int argc,
                                 char **argv,
                                 argh::parser &cmd,
                                 std::string &description)>
    function_map;

/**
 * @param arguments
 * @param options
 * @param cmd
 * @param argc
 * @param argv
 */
void ValidateCmdInput(
    std::vector<std::string> &arguments,
    std::vector<std::string> &options,
    argh::parser &cmd,
    int argc,
    char **argv);

/**
 * @param cmd
 */
void DisplayDebug(argh::parser &cmd);

/**
 * @param in_function_map
 * @param cmd
 * @param argc
 * @param argv
 */
void HandleMenu(
    std::map<std::string, void (*)(
                              int argc,
                              char **argv,
                              argh::parser &cmd,
                              std::string &description)> &in_function_map,
    argh::parser &cmd,
    int argc,
    char **argv);
};  // namespace EQEmuCommand

#endif  // EQEMU_EQEMU_COMMAND_HANDLER_H