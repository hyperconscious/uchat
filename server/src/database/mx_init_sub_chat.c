#include "../inc/database.h"

int mx_init_sub_chat(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db,   "DELETE FROM chat WHERE id = ?1; \
                                     DELETE FROM chat_participant WHERE chat_id = ?1; \
                                     DELETE FROM message WHERE chat_id = ?1;", -1, statement, 0);
}
