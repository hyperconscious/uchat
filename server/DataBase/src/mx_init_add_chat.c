#include "../inc/database.h"

int mx_init_add_chat(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "INSERT INTO \"main\".\"chats\"(\"name\", \"owner_id\") VALUES (?, ?);", -1, statement, 0);
}
