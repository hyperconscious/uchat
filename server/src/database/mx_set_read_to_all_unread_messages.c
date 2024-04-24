#include "database.h"

int mx_set_read_to_all_unread_messages(sqlite3* db, int user_id, int chat_id)
{
    sqlite3_stmt *get_last_message;

    int result = 0;

    int tmp;
    t_db_message *messages;
    mx_get_last_messages(db, chat_id, "", 1, &messages, &tmp);
    
    if(tmp < 1)
    {
        return SQLITE_ERROR;
    }

    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE chat_participant SET last_readed_message_id = ? WHERE chat_id = ? AND user_id = ?", -1, &get_last_message, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 1, messages[0].id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 2, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 3, user_id), result);

    if(sqlite3_step(get_last_message) != SQLITE_DONE)
    {
        return sqlite3_step(get_last_message);
    }

    sqlite3_finalize(get_last_message);
    return 0;
}
