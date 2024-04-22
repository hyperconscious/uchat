#include "database.h"

int mx_change_username(sqlite3 *db, uint32_t id, char* new_name)
{
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, "UPDATE user_data SET name = ? WHERE id = ?;", -1, &stmt, 0);
    sqlite3_reset(stmt);
    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    int res = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if(res != SQLITE_DONE) return res;
    return 0;
}


