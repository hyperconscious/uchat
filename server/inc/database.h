#pragma once
#include "../SQLite/sqlite3.h"
#include <stdlib.h>
#include <stdio.h> 
#include <crypt.h>

#define MX_TRY_FUNCTION(f, res) res = f; if(res) return res;
#define DATABASE "server/Messenger.db"

typedef struct database_info
{
    sqlite3 *database;
    sqlite3_stmt *addusr_stmt;
    sqlite3_stmt *subusr_stmt;
    sqlite3_stmt *checkpass_stmt;
    sqlite3_stmt *addmsg_stmt;
    sqlite3_stmt *submsg_stmt;
    sqlite3_stmt *addchat_stmt;
    sqlite3_stmt *subchat_stmt;
    sqlite3_stmt *addusrtochat_stmt;
    sqlite3_stmt *subusrtochat_stmt;
    sqlite3_stmt *get_last_messages_stmt;
    sqlite3_stmt *get_user_id_by_login;
} t_db_info;


int mx_recreate_tables(sqlite3 *db);


//statements initialization
int mx_init_add_user(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_user(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_check_password(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_message(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_message(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_chat(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_add_chat_participant(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_sub_chat_participant(sqlite3 *db, sqlite3_stmt **statement);

int mx_init_get_last_messages(sqlite3 *db, sqlite3_stmt **statement);

//db_info
int mx_init_db_info(const char *db, t_db_info **info);

int mx_destroy_db_info(t_db_info **info);


//user_data
int mx_add_user(t_db_info *info, const char *name, const char *password, int *id_of_new_user);

int mx_sub_user(t_db_info *info, long id);

int mx_check_password(t_db_info *info, long id, char *password);


//message
int mx_add_message(t_db_info *info, char *text, int user_id, int chat_id, float time);

int mx_sub_message(t_db_info *info, int id);

//chat
int mx_add_chat(t_db_info *info, char *name, int owner_id, int *id_of_new_chat);

int mx_sub_chat(t_db_info *info, int id);
    

//chat_partipicant
int mx_add_usr_to_chat(t_db_info *info, int user_id, int chat_id);

int mx_sub_usr_from_chat(t_db_info *info, int user_id, int chat_id);

//selectors

int mx_get_last_messages(t_db_info *info, int chat_id, int max_rows, void(*callback)(sqlite3_stmt*));

//int ms_get_user_id_by_login(t_db_info *info, char *login, int *result_id); //TODO

//utils
const char *get_last_error(t_db_info *info);
