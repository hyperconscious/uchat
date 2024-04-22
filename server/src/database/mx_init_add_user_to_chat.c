#include "database.h"

int mx_init_add_user_to_chat(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "INSERT INTO \"main\".\"chat_participant\"(\"user_id\", \"chat_id\") VALUES (?, ?);", -1, statement, 0);
}
