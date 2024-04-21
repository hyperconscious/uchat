#include "handle_db_chat.h"

int mx_get_users_from_chat(sqlite3 *db, long chat_id, int max_count, long **result_ids, int *result_count) 
{
    (*result_count) = 0;
    sqlite3_stmt *statement;
    int rc = sqlite3_prepare_v2(db, "SELECT user_data.id FROM chat_patricipant WHERE chat_id = ? LIMIT ?", -1, &statement, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    sqlite3_bind_int64(statement, 1, chat_id);
    sqlite3_bind_int64(statement, 2, max_count);
    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        (*result_count)++;
    }
    if (rc != SQLITE_DONE) {
       fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(db));
       *result_count = 0;
    }

    sqlite3_reset(statement);
    sqlite3_bind_int64(statement, 1, chat_id);
    sqlite3_bind_int64(statement, 2, max_count);

    *result_ids = malloc(*result_count * sizeof(long));
    for(int i = 0; i < *result_count; i++)
    {
        sqlite3_step(statement);
        (*result_ids)[i] = sqlite3_column_int64(statement, 0);
    }
    sqlite3_finalize(statement);
    return 0;
}
