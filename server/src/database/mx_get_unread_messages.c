#include "database.h"

int mx_get_unread_messages(sqlite3* db, int user_id, int chat_id, t_db_message **result_messages, int *result_count)
{
    
    sqlite3_stmt *get_last_message;

    int result = 0;

    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "SELECT last_readed_message_id FROM chat_participant WHERE user_id = ? AND chat_id = ?;", -1, &get_last_message, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 2, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 1, user_id), result);
    int lstat = sqlite3_step(get_last_message);
    if(lstat != SQLITE_ROW)
    {
        return lstat;
    }
    int msg_id = sqlite3_column_int64(get_last_message, 0);
    lstat = sqlite3_step(get_last_message);
    sqlite3_finalize(get_last_message);
    if(lstat != SQLITE_DONE)
    {
        return lstat;
    }
    t_db_message *message = mx_get_message_by_id(db, msg_id);

    if(message == NULL)
    {
        mx_get_last_messages(db, chat_id, "", -1, result_messages, result_count);
        
        return 0;
    }

    sqlite3_stmt *read_stmt;
    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "SELECT id, text, user_id, time, chat_id FROM message WHERE time > ? AND chat_id = ?;", -1, &read_stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(read_stmt, 1, message->time, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int64(read_stmt, 2, message->chat_id), result);

    *result_count = 0;
    int stat;
    while((stat = sqlite3_step(read_stmt)) == SQLITE_ROW)
    {
        (*result_count)++;
    }
    
    if(stat != SQLITE_DONE)
    {
        sqlite3_finalize(read_stmt);
        return stat;
    }

    MX_TRY_FUNCTION(sqlite3_reset(read_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(read_stmt, 1, message->time, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int64(read_stmt, 2, message->chat_id), result);
    
    *result_messages = malloc(sizeof(t_db_message) * (*result_count));

    for(int i = 0; i < *result_count; i++)
    {
        stat = sqlite3_step(read_stmt);
        if(stat != SQLITE_ROW)
            return stat;
        (*result_messages)[i].text = strdup((const char*)sqlite3_column_text(read_stmt, 1));
        (*result_messages)[i].time = strdup((const char*)sqlite3_column_text(read_stmt, 3));
        (*result_messages)[i].id = sqlite3_column_int64(read_stmt, 0);
        (*result_messages)[i].user_id = sqlite3_column_int64(read_stmt, 2);
        (*result_messages)[i].chat_id = sqlite3_column_int64(read_stmt, 4);
    }

    if(sqlite3_step(read_stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(read_stmt);
        return stat;
    }
    
    MX_TRY_FUNCTION(sqlite3_finalize(read_stmt), result);
    return 0;
}
