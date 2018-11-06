// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef BATTLEGROUND_HPP
#define BATTLEGROUND_HPP

#include "../common/cbasetypes.hpp"
#include "../common/mmo.hpp" // struct party

#define MAX_BG_MEMBERS 50

struct battleground_member_data {
	unsigned short x, y;
	struct map_session_data *sd;
	unsigned afk : 1;
};

struct battleground_data {
	unsigned int bg_id;
	int count;
	time_t creation_tick; // Creation of this Team
 	struct battleground_member_data members[MAX_BG_MEMBERS];
	// Team Leader and BG Skills features
	int leader_char_id;
	int skill_block_timer[MAX_GUILDSKILL];
	unsigned int color;
	// Party - Faction ID
	int pf_id;
	// Fake Guild Link
	struct guild *g;
	// BG Cementery
	unsigned short mapindex, x, y;
	// Logout Event
	bool reveal_pos, reveal_flag;
	char logout_event[EVENT_NAME_LENGTH];
	char die_event[EVENT_NAME_LENGTH];
	// Score Board
	int team_score;
};

struct queue_member {
	int position;
	struct map_session_data *sd;
	struct queue_member *next;
};

struct queue_data {
	unsigned int q_id;
	int min_level, users;
	struct queue_member *first, *last;
	char queue_name[50], join_event[EVENT_NAME_LENGTH];
};

extern struct guild bg_guild[];
extern const unsigned int bg_colors[];
void do_init_battleground(void);
void do_final_battleground(void);

struct battleground_data* bg_team_search(int bg_id);
struct guild* bg_guild_get(int bg_id);
int bg_send_dot_remove(struct map_session_data *sd);
int bg_team_get_id(struct block_list *bl);
struct map_session_data* bg_getavailablesd(struct battleground_data *bg);

int bg_create(unsigned short mapindex, short rx, short ry, int guild_index, const char *ev, const char *dev);
int bg_team_join(int bg_id, struct map_session_data *sd);
int bg_team_clean(int bg_id, bool remove);
int bg_team_leave(struct map_session_data *sd, int flag);
int bg_team_warp(int bg_id, unsigned short mapindex, short x, short y);
int bg_member_respawn(struct map_session_data *sd);
int bg_send_message(struct map_session_data *sd, const char *mes, int len);
int bg_countlogin(struct map_session_data *sd, bool check_bat_room);
void bg_team_getitem(int bg_id, int nameid, int amount);
void bg_team_get_kafrapoints(int bg_id, int amount);
void bg_team_rewards(int bg_id, int nameid, int amount, int kafrapoints, int quest_id, const char *var, int add_value, int bg_arena, int bg_result);

struct queue_data* bg_queue_search(int q_id);
int bg_queue_create(const char* queue_name, const char* join_event, int min_level);
int bg_queue_destroy(int q_id);
int bg_queue_leave(struct map_session_data *sd, int q_id);
void bg_queue_leaveall(struct map_session_data *sd);
int bg_queue_join(struct map_session_data *sd, int q_id);

struct queue_member* bg_queue_member_get(struct queue_data *qd, int position);
int bg_queue_member_remove(struct queue_data *qd, int id);

int bg_checkskill (struct battleground_data *bg, int id);
void bg_block_skill_status (struct battleground_data *bg, int skillnum);
void bg_block_skill_start (struct battleground_data *bg, int skillnum, unsigned int time);
int bg_block_skill_end (int tid, unsigned int tick, int id, intptr_t data);

void bg_reload(void);
void bg_guild_build_data(void);

#endif /* BATTLEGROUND_HPP */
