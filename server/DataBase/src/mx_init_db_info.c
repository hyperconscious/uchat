#include "../inc/database.h"

int mx_init_db_info(const char *db, t_db_info **info)
{

    *info = malloc(sizeof(t_db_info));
    t_db_info *inf = *info;
    int result = 0;

    TRY_FUNCTION(sqlite3_open_v2("Messenger.db", &inf->database, SQLITE_OPEN_READWRITE, NULL), result);

    TRY_FUNCTION(mx_init_add_user(inf->database, &inf->addusr_stmt), result);
    TRY_FUNCTION(mx_init_sub_user(inf->database, &inf->subusr_stmt), result);

    TRY_FUNCTION(mx_init_check_password(inf->database, &inf->checkpass_stmt), result);

    TRY_FUNCTION(mx_init_add_message(inf->database, &inf->addmsg_stmt), result);
    TRY_FUNCTION(mx_init_sub_message(inf->database, &inf->submsg_stmt), result);

    TRY_FUNCTION(mx_init_add_chat(inf->database, &inf->submsg_stmt), result);
    TRY_FUNCTION(mx_init_sub_chat(inf->database, &inf->submsg_stmt), result);

    TRY_FUNCTION(mx_init_add_chat_participant(inf->database, &inf->submsg_stmt), result);
    TRY_FUNCTION(mx_init_sub_chat_participant(inf->database, &inf->submsg_stmt), result);
    
    return result;
}
