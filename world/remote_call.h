#ifndef WORLD_REMOTE_CALL_H
#define WORLD_REMOTE_CALL_H

#include <map>
#include <string>
#include <vector>

typedef void (*RemoteCallHandler)(const std::string &, const std::string &, const std::string &, const std::vector<std::string> &);

void RemoteCallResponse(const std::string &connection_id, const std::string &request_id, const std::map<std::string, std::string> &res, const std::string &error);

void register_remote_call_handlers();
void handle_rc_list_zones(const std::string &method, const std::string &connection_id, const std::string &request_id, const std::vector<std::string> &params);
void handle_rc_get_zone_info(const std::string &method, const std::string &connection_id, const std::string &request_id, const std::vector<std::string> &params);
void handle_rc_relay(const std::string &method, const std::string &connection_id, const std::string &request_id, const std::vector<std::string> &params);
void handle_rc_get_file_contents(const std::string &method, const std::string &connection_id, const std::string &request_id, const std::vector<std::string> &params);
void handle_rc_save_file_contents(const std::string &method, const std::string &connection_id, const std::string &request_id, const std::vector<std::string> &params);

#endif
