#include "database.h"

int mx_get_chats_by_user_id(sqlite3_stmt *stmt, int user_id, int max_rows,
        t_db_chat **chats, uint16_t *result_count)
{
    int result = 0;
    *result_count = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, max_rows), result);

   /* int stat = sqlite3_step(stmt);
    if(stat != SQLITE_ROW){
     //   fprintf(stderr, "No result");
        return stat;
    }*/
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        (*result_count)++;
    }
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, max_rows), result);
    *chats = malloc(sizeof(t_db_chat) * (*result_count));
    for(int i = 0; i < *result_count; i++)
    {
        sqlite3_step(stmt);
        (*chats)[i].id = sqlite3_column_int64(stmt, 0);
        (*chats)[i].name = strdup((const char *)sqlite3_column_text(stmt, 1));
        (*chats)[i].owner_id = sqlite3_column_int64(stmt, 2);
        (*chats)[i].creation_time = strdup((const char *)sqlite3_column_text(stmt, 3));
        (*chats)[i].is_private = sqlite3_column_int64(stmt, 4);
    }
    return 0;
}

