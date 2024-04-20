#include "database.h"

char *mx_get_login_by_id(sqlite3 *db, const int id) {
    sqlite3_stmt *statement;
    const char *sql = "SELECT name FROM user_data WHERE id == ?";
    char *login = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, id);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            login = strdup((char *)sqlite3_column_text(statement, 0));
        }

        sqlite3_finalize(statement);
    }
    return login;;
}
