#include "database.h"

int mx_init_get_chats_id_by_name(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "SELECT chat.id, chat.name, chat.owner_id FROM chat WHERE chat.name LIKE '%%' || ?1 || '%%' LIMIT ?", -1, statement, 0);
}
