#include "../inc/database.h"

int mx_destroy_db_info(t_db_info **info)
{

    int result = 0;
    TRY_FUNCTION(sqlite3_finalize((*info) -> addusr_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> subusr_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> checkpass_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> addchat_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> subchat_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> addmsg_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> submsg_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> addusrtochat_stmt), result);
    TRY_FUNCTION(sqlite3_finalize((*info) -> subusrtochat_stmt), result);
    sqlite3_close_v2((*info)->database);
    free(*info);
    (*info) = 0;

    return result;
}
