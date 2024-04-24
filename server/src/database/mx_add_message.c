#include "../inc/database.h"

int mx_add_message(sqlite3_stmt *stmt, char *text, int user_id, int chat_id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
   // printf("1 %d - %d - %s\n", user_id , chat_id, text);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, user_id), result);
   // printf("1\n");
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, chat_id), result);
   // printf("1\n");
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 3, text, -1, SQLITE_STATIC), result);
   // printf("1\n");
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);
   // printf("%d\n", sqlite3_step(stmt));
    
    return 0;
}
