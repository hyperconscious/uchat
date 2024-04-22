#include "../inc/database.h"

int mx_add_user_to_chat(sqlite3_stmt *stmt, int user_id, int chat_id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, chat_id), result);
  //  if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        // Обработка ошибки выполнения запроса
        fprintf(stderr, "Error adding user to chat: %s\n", sqlite3_errmsg(sqlite3_db_handle(stmt)));
        return result;
    }
    
    return 0;
}
