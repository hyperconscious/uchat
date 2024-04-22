#pragma once

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "types.h"
#ifdef __MACH__

#include <unistd.h>

#else

#include <crypt.h>
#endif

#define MX_TRY_FUNCTION(f, res) res = f; if(res) return res;
#define DATABASE "server/Messenger.db"

// typedef struct database_info {
//     sqlite3 *database;
//     sqlite3_stmt *addusr_stmt;
//     sqlite3_stmt *subusr_stmt;
//     sqlite3_stmt *checkpass_stmt;
//     sqlite3_stmt *addmsg_stmt;
//     sqlite3_stmt *submsg_stmt;
//     sqlite3_stmt *addchat_stmt;
//     sqlite3_stmt *subchat_stmt;
//     sqlite3_stmt *addusrtochat_stmt;
//     sqlite3_stmt *subusrtochat_stmt;
//     sqlite3_stmt *get_last_messages_stmt;
//     sqlite3_stmt *get_user_id_by_login_stmt;
// } t_db_info;


int mx_recreate_tables(sqlite3 *db);


//statements initialization
int mx_init_add_user(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_user(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_check_password(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_message(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_message(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_get_chats_by_user_id(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_get_chats_by_name(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_user_to_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_user_from_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_get_last_messages(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_find_id_by_user(sqlite3 *db, sqlite3_stmt **statement);


//db_info
//int mx_init_db_info(const char *db, sqlite3_stmt *stmt);

//int mx_init_single_db_info(const char *db, t_db_info **info, sqlite3_stmt ** stmt, int(*statement_initialisator)(sqlite3 *, sqlite3_stmt **));

//int mx_destroy_db_info(t_db_info **info);


//user_data
int mx_add_user(sqlite3_stmt *stmt, const char *name, const char *password, uint16_t lang);

int mx_sub_user(sqlite3_stmt *stmt, long id);

int mx_check_password(sqlite3_stmt *stmt, char *login, char *password);


//message
int mx_add_message(sqlite3_stmt *stmt, char *text, int user_id, int chat_id, float time);

int mx_sub_message(sqlite3_stmt *stmt, int id);

int mx_sub_chat(sqlite3_stmt *stmt, int id);


//chat_partipicant
int mx_add_user_to_chat(sqlite3_stmt *stmt, int chat_id, int user_id);

int mx_sub_user_from_chat(sqlite3_stmt *stmt, int user_id, int chat_id);

//selectors
long mx_find_id_by_user(sqlite3_stmt *stmt, char* username);
long mx_get_user_id_by_login(sqlite3_stmt *stmt, char *login);

int mx_get_users_from_chat(sqlite3 *db, long chat_id, int max_count, uint32_t
        **result_ids, uint16_t *result_count); 

char **mx_get_users_by_language(sqlite3 *db, int language, uint16_t *count);


char **mx_get_chat_names(sqlite3 *db, int owner_id, uint16_t *count);

//chat
int mx_add_chat(sqlite3_stmt *stmt, char *name, int owner_id);

int mx_get_chats_by_user_id(sqlite3_stmt *stmt, int user_id, int max_rows, t_db_chat **chats, uint16_t *result_count);

int mx_get_chats_by_name(sqlite3_stmt *stmt, char *name, int max_rows, t_db_chat **chats, uint16_t *result_count);

int mx_get_chat_by_id(sqlite3 *db, sqlite3_stmt **statement, long *result_ids);
//int mx_find_id_by_login(t_db_info *info, char* username);

char **mx_find_users_by_login(sqlite3 *db, uint8_t max_counts, const char *name, uint16_t *count);

char *mx_get_login_by_id(sqlite3 *db, const int id);

int mx_get_last_messages(sqlite3_stmt *stmt, int chat_id, int max_rows);

//utils
const char *get_last_error(sqlite3_stmt *stmt);

//testing
void mx_test_db_all(void);


uint16_t mx_get_lang_by_id(sqlite3 *db, uint32_t user_id);
