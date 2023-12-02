#ifndef _EQEMU_VERSION_H
#define _EQEMU_VERSION_H

#define LOGIN_VERSION "0.8.0"
#define EQEMU_PROTOCOL_VERSION "0.3.10"

#define CURRENT_VERSION "2.0"

/**
 * Every time a Database SQL is added to Github increment CURRENT_BINARY_DATABASE_VERSION
 * number and make sure you update the manifest
 *
 * Manifest: https://github.com/EQEmu/Server/blob/master/utils/sql/db_update_manifest.txt
 */

#define CURRENT_BINARY_DATABASE_VERSION 9075

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__
#ifndef WIN32
#define LAST_MODIFIED __TIME__
#else
#define LAST_MODIFIED __TIMESTAMP__
#endif

#endif
