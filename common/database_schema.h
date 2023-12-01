#ifndef EQEMU_DATABASE_SCHEMA_H
#define EQEMU_DATABASE_SCHEMA_H

#include <vector>
#include <map>
#include <string>

namespace DatabaseSchema {

/**
 * Gets player tables
 *
 * @return
 */
static std::vector<std::string> GetPlayerTables() {
	return {
	    "account",
	    "account_flags",
	    "account_ip",
	    "account_rewards",
	    "character_alternate_abilities",
	    "character_consent",
	    "character_bandolier",
	    "character_bind",
	    "character_buffs",
	    "character_corpse_items",
	    "character_corpse_items_backup",
	    "character_corpses",
	    "character_corpses_backup",
	    "character_currency",
	    "character_data",
	    "character_faction_values",
	    "character_inspect_messages",
	    "character_inventory",
	    "character_keyring",
	    "character_languages",
	    "character_lookup",
	    "character_material",
	    "character_memmed_spells",
	    "character_pet_buffs",
	    "character_pet_info",
	    "character_pet_inventory",
	    "character_skills",
	    "character_soulmarks",
	    "character_spells",
	    "character_timers",
	    "character_zone_flags",
	    "discovered_items",
	    "friends",
	    "guilds",
	    "guild_ranks",
	    "guild_members",
	    "mail",
	    "petitions",
	    "player_titlesets",
	    "quest_globals",
	    "spell_globals",
	    "client_version",
	    "commands_log",
	    "titles",
	    "trader",
	};
}

/**
 * Gets content tables
 *
 * @return
 */
static std::vector<std::string> GetContentTables() {
	return {
	    "aa_actions",
	    "aa_effects",
	    "altadv_vars",
	    "base_data",
	    "blocked_spells",
	    "books",
	    "char_create_combinations",
	    "char_create_point_allocations",
	    "damageshieldtypes",
	    "doors",
	    "faction_list",
	    "faction_list_mod",
	    "fishing",
	    "forage",
	    "goallists",
	    "graveyard",
	    "grid",
	    "grid_entries",
	    "ground_spawns",
	    "horses",
	    "items",
	    "keyring_data",
	    "level_exp_mods",
	    "lootdrop",
	    "lootdrop_entries",
	    "loottable",
	    "loottable_entries",
	    "merchantlist",
	    "npc_emotes",
	    "npc_faction",
	    "npc_faction_entries",
	    "npc_spells",
	    "npc_spells_entries",
	    "npc_spells_effects",
	    "npc_spells_effects_entries",
	    "npc_types",
	    "npc_types_metadata",
	    "npc_types_tint",
	    "object",
	    "pets",
	    "proximities",
	    "races",
	    "skill_caps",
	    "skill_difficulty",
	    "spawn2",
	    "spawn_conditions",
	    "spawn_condition_values",
	    "spawn_events",
	    "spawnentry",
	    "spawngroup",
	    "spells_en",
	    "spells_new",
	    "start_zones",
	    "starting_items",
	    "tradeskill_recipe",
	    "tradeskill_recipe_entries",
	    "traps",
	    "zone",
	    "zone_points",
	    "zone_server",
	    "zone_state_dump",
	    "zoneserver_auth"};
}

/**
 * Gets server tables
 *
 * @return
 */
static std::vector<std::string> GetServerTables() {
	return {
	    "Banned_IPs",
	    "chatchannels",
	    "command_settings",
	    "eqtime",
	    "gm_ips",
	    "hackers",
	    "launcher",
	    "launcher_zones",
	    "logsys_categories",
	    "name_filter",
	    "rule_sets",
	    "rule_values",
	    "variables",
	};
}

/**
 * Gets QueryServer tables
 *
 * @return
 */
static std::vector<std::string> GetQueryServerTables() {
	return {
	    "qs_merchant_transaction_log",
	    "qs_player_aa_purchase_log",
	    "qs_player_aa_rate_hourly",
	    "qs_player_coin_move_log",
	    "qs_player_events",
	    "qs_player_ground_spawns_log",
	    "qs_player_handin_log",
	    "qs_player_item_delete_log",
	    "qs_player_item_desyncs_log",
	    "qs_player_item_move_log",
	    "qs_player_killed_by_log",
	    "qs_player_loot_records_log",
	    "qs_player_npc_kill_log",
	    "qs_player_qglobal_updates_log",
	    "qs_player_speech",
	    "qs_player_trade_items_log",
	    "qs_player_trade_log",
	    "qs_player_ts_event_log",
	    "qs_trader_audit",
	};
}

/**
 * Gets state tables
 * Tables that keep track of server state
 *
 * @return
 */

static std::vector<std::string> GetStateTables() {
	return {
	    "bugs",
	    "eventlog",
	    "group_id",
	    "group_leaders",
	    "item_tick",
	    "merchantlist_temp",
	    "object_contents",
	    "raid_details",
	    "raid_members",
	    "reports",
	    "respawn_times",
	    "saylink",
	    "webdata_character",
	    "webdata_servers"};
}
}  // namespace DatabaseSchema

#endif  // EQEMU_DATABASE_SCHEMA_H