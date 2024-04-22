#include "database.h"

int mx_get_last_messages(sqlite3 *db, int chat_id, char *search_text, int max_rows, bool set_readed, t_db_message **messages, int *result_count)
{
    
    int result = 0;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT message.id, message.text, message.user_id, message.time, message.is_readed FROM message WHERE chat_id == ? AND text LIKE '%%' || ? || '%%' ORDER BY time ASC LIMIT ?", -1, &stmt, 0);
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, chat_id), result);
    
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 2, search_text, -1, 0), result);
    
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 3, max_rows), result);
    
    int stat = sqlite3_step(stmt);
    
    if(stat != SQLITE_ROW) return stat;
    *result_count = 1;
    while(sqlite3_step(stmt) != SQLITE_DONE)
    {
        (*result_count)++;
    }

    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 2, search_text, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 3, max_rows), result);
    if(set_readed)
    {
        sqlite3_stmt *set_read_stmt;
        MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE message SET is_readed = 1 WHERE chat_id = ? AND text LIKE '%%' || ? || '%%'", -1, &set_read_stmt, 0), result);
        MX_TRY_FUNCTION(sqlite3_reset(set_read_stmt), result);
        MX_TRY_FUNCTION(sqlite3_bind_int(set_read_stmt, 1, chat_id), result);
        MX_TRY_FUNCTION(sqlite3_bind_text(set_read_stmt, 2, search_text, -1, 0), result);
        sqlite3_step(set_read_stmt);
        sqlite3_finalize(set_read_stmt);
    }

    *messages = malloc(sizeof(t_db_message) * (*result_count));

    for(int i = 0; i < *result_count; i++)
    {
        sqlite3_step(stmt);
        (*messages)[i].text = strdup((const char*)sqlite3_column_text(stmt, 1));
        (*messages)[i].time = strdup((const char*)sqlite3_column_text(stmt, 3));
        (*messages)[i].id = sqlite3_column_int64(stmt, 0);
        (*messages)[i].user_id = sqlite3_column_int64(stmt, 2);
        (*messages)[i].is_readed = sqlite3_column_int(stmt, 4);
    }

    sqlite3_finalize(stmt);
    return 0;
}

