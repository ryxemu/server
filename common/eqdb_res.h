#ifndef EQDBRes_H_
#define EQDBRes_H_

#include <string>
#include <vector>
#include <map>
#include "types.h"
#include "database.h"
#include <mysql.h>

// this is the main object exported to perl.
class EQDBRes {
   public:
	EQDBRes(MYSQL_RES *r) { res = r; }
	~EQDBRes() { finish(); }

	// BEGIN PERL EXPORT
	unsigned long num_rows() { return (res) ? mysql_num_rows(res) : 0; }
	unsigned long num_fields() { return (res) ? mysql_num_fields(res) : 0; }
	void DESTROY() {}
	void finish() {
		if (res) mysql_free_result(res);
		res = nullptr;
	};
	std::vector<std::string> fetch_row_array();
	std::map<std::string, std::string> fetch_row_hash();
	unsigned long *fetch_lengths() { return (res) ? mysql_fetch_lengths(res) : 0; }
	// END PERL EXPORT

   private:
	MYSQL_RES *res;
};

#endif /*EQDBRes_H_*/
