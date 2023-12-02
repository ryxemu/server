#include "global_define.h"
#include "eqdb_res.h"
#include <mysql.h>

std::vector<std::string> EQDBRes::fetch_row_array() {
	std::vector<std::string> array;
	if (res == nullptr)
		return (array);

	int count = mysql_num_fields(res);
	MYSQL_ROW row = mysql_fetch_row(res);
	for (int i = 0; i < count; i++)
		array.push_back(row[i]);

	return array;
}

std::map<std::string, std::string> EQDBRes::fetch_row_hash() {
	std::map<std::string, std::string> rowhash;
	if (res == nullptr)
		return (rowhash);

	MYSQL_FIELD *fields;
	MYSQL_ROW row;
	unsigned long num_fields, i;

	if (res && (num_fields = mysql_num_fields(res)) && (row = mysql_fetch_row(res)) != nullptr && (fields = mysql_fetch_fields(res)) != nullptr) {
		for (i = 0; i < num_fields; i++) {
			rowhash[fields[i].name] = (row[i] ? row[i] : "");
		}
	}

	return rowhash;
}
