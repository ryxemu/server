#ifndef EQEMU_DATABASE_DUMP_SERVICE_H
#define EQEMU_DATABASE_DUMP_SERVICE_H

class DatabaseDumpService {
   public:
	void Dump();
	bool IsDumpAllTables() const;
	void SetDumpAllTables(bool dump_all_tables);
	bool IsDumpWithNoData() const;
	void SetDumpWithNoData(bool dump_with_no_data);
	bool IsDumpSystemTables() const;
	void SetDumpSystemTables(bool dump_system_tables);
	bool IsDumpContentTables() const;
	void SetDumpContentTables(bool dump_content_tables);
	bool IsDumpPlayerTables() const;
	void SetDumpPlayerTables(bool dump_player_tables);
	// bool IsDumpLoginServerTables() const;
	// void SetDumpLoginServerTables(bool dump_login_server_tables);
	bool IsDumpTableLock() const;
	void SetDumpTableLock(bool dump_table_lock);
	bool IsDumpWithCompression() const;
	void SetDumpWithCompression(bool dump_with_compression);
	const std::string &GetDumpPath() const;
	void SetDumpPath(const std::string &dump_path);
	const std::string &GetDumpFileName() const;
	void SetDumpFileName(const std::string &dump_file_name);
	bool IsDumpQueryServerTables() const;
	void SetDumpQueryServerTables(bool dump_query_server_tables);
	bool IsDumpOutputToConsole() const;
	void SetDumpOutputToConsole(bool dump_output_to_console);
	bool IsDumpDropTableSyntaxOnly() const;
	void SetDumpDropTableSyntaxOnly(bool dump_drop_table_syntax_only);
	bool IsDumpStateTables() const;
	void SetDumpStateTables(bool dump_state_tables);

   private:
	bool dump_all_tables = false;
	bool dump_state_tables = false;
	bool dump_system_tables = false;
	bool dump_content_tables = false;
	bool dump_player_tables = false;
	bool dump_query_server_tables = false;
	// bool        dump_login_server_tables = false;
	bool dump_with_no_data = false;
	bool dump_table_lock = false;
	bool dump_with_compression = false;
	bool dump_output_to_console = false;
	bool dump_drop_table_syntax_only = false;
	std::string dump_path;
	std::string dump_file_name;

	bool IsMySQLInstalled();
	std::string GetMySQLVersion();
	std::string GetBaseMySQLDumpCommand();
	std::string GetPlayerTablesList();
	std::string GetSystemTablesList();
	std::string GetStateTablesList();
	std::string GetContentTablesList();
	// std::string GetLoginTableList();
	bool IsTarAvailable();
	bool Is7ZipAvailable();
	bool HasCompressionBinary();
	std::string GetDumpFileNameWithPath();
	std::string GetSetDumpPath();
	std::string GetQueryServTables();
};

#endif  // EQEMU_DATABASE_DUMP_SERVICE_H