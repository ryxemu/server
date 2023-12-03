#ifndef EQDB_H_
#define EQDB_H_

#include <string>
#include <vector>
#include <map>
#include "types.h"
#include "eqdb_res.h"
#include <mysql.h>

// this is the main object exported to perl.
class EQDB {
	EQDB();

   public:
	static EQDB *Singleton() { return (&s_EQDB); }

	static void SetMySQL(MYSQL *m) { s_EQDB.mysql_ref = m; }

	// BEGIN PERL EXPORT
	// NOTE: you must have a space after the * of a return value

	unsigned int field_count();
	unsigned long affected_rows();
	unsigned long insert_id();
	unsigned int get_errno();
	Const_char *error();
	EQDBRes *query(Const_char *q);
	std::string escape_string(const char* from);   // NOT THREAD SAFE! (m_escapeBuffer)
	// END PERL EXPORT

   private:
	std::string m_escapeBuffer;
	static EQDB s_EQDB;
	MYSQL *mysql_ref;
};

#endif /*EQDB_H_*/
