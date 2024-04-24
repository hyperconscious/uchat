#include "../inc/database.h"

int mx_sub_chat(sqlite3 *db, int id)
{
    // return sqlite3_prepare_v2(db,   "DELETE FROM chat WHERE id = ?1; \
    //                                  DELETE FROM chat_participant WHERE chat_id = ?1; \
    //                                  DELETE FROM message WHERE chat_id = ?1;", -1, statement, 0);
    int result = 0;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "DELETE FROM chat WHERE id = ?;", -1, &stmt, 0);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);

    sqlite3_prepare_v2(db, "DELETE FROM chat_participant WHERE chat_id = ?;", -1, &stmt, 0);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);

    sqlite3_prepare_v2(db, "DELETE FROM message WHERE chat_id = ?;", -1, &stmt, 0);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    return 0;
}
