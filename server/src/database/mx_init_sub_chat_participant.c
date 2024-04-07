#include "../inc/database.h"

int mx_init_sub_chat_participant(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "DELETE FROM chat_participant WHERE user_id = ? AND chat_id = ?", -1, statement, 0);
}
