#include "database.h"

uint16_t mx_get_lang_by_id(sqlite3 *db, uint32_t user_id) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT language FROM user_data WHERE id = ?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, user_id);
    
    uint16_t lang = 0;
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        lang = sqlite3_column_int64(stmt, 0); 
    }
    return lang;
    
    }


