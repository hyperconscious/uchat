#include "../inc/database.h"

const char *get_last_error(t_db_info *info)
{   
    return sqlite3_errmsg(info->database);
}
