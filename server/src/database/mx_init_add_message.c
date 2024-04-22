#include "../inc/database.h"

int mx_init_add_message(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "INSERT INTO message (time, user_id, chat_id, text, is_readed) VALUES (datetime('now', 'localtime'), ?, ?, ?, 0)", -1, statement, 0);
}
