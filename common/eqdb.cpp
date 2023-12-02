#include "global_define.h"
#include "eqdb.h"
#include "database.h"
#include <mysql.h>
#include <cstring>

EQDB EQDB::s_EQDB;

EQDB::EQDB() {
}

unsigned int EQDB::field_count() {
	return mysql_field_count(mysql_ref);
}

unsigned long EQDB::affected_rows() {
	return mysql_affected_rows(mysql_ref);
}

unsigned long EQDB::insert_id() {
	return mysql_insert_id(mysql_ref);
}

unsigned int EQDB::get_errno() {
	return mysql_errno(mysql_ref);
}

Const_char *EQDB::error() {
	return mysql_error(mysql_ref);
}

EQDBRes *EQDB::query(Const_char *q) {
	if (mysql_real_query(mysql_ref, q, strlen(q)) == 0) {
		if (mysql_field_count(mysql_ref)) {
			MYSQL_RES *r = mysql_store_result(mysql_ref);
			return new EQDBRes(r);
		} else {
			// no result, give them back a 'true but empty' result set
			return (new EQDBRes(nullptr));
		}
	}

	return nullptr;
}

// Re-Write to make thread safe
std::string EQDB::escape_string(const char* from) {
    int len = strlen(from);
    char* res = new char[len * 2 + 1];

    // Use a local buffer for escaping
    mysql_real_escape_string(mysql_ref, res, from, len);

    // Create a string from the escaped char array
    std::string escapedString(res);

    // Clean up allocated memory
    delete[] res;

    return escapedString;
}
