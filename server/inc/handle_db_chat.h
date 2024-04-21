#pragma once

#include "database.h"
#include "types.h"

//chat
int mx_add_chat(sqlite3_stmt *stmt, char *name, int owner_id);

int mx_get_chats_by_user_id(sqlite3_stmt *stmt, int user_id, int max_rows, t_chat **chats ,int *result_count);

int mx_get_chats_by_name(sqlite3_stmt *stmt, char *name, int max_rows, t_chat **chats ,int *result_count);

int mx_get_chat_by_id(sqlite3 *db, sqlite3_stmt **statement, long *result_ids);
