#include "../inc/database.h"

long mx_find_id_by_user(t_db_info *info, char* username)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info->get_user_id_by_login), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(info->get_user_id_by_login, 1, username, -1, SQLITE_STATIC), result);


    long id = -1;
    while ((sqlite3_step(info->get_user_id_by_login)) == SQLITE_ROW) {
        id = sqlite3_column_int(info->get_user_id_by_login, 0); // Get the value of the 'id' column  
    }


    return id;
    
}

