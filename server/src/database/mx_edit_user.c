#include "database.h"

int mx_edit_user(sqlite3 *db, int user_id, char *new_name, char *old_password, char *new_password, int new_lang)
{
    sqlite3_stmt *edit_stmt;
    int result = 0;
    char *login = mx_get_login_by_id(db, user_id);
    sqlite3_stmt *pass;
    mx_init_check_password(db, &pass);
    if(!mx_check_password(pass, login, old_password))
    {
        fprintf(stderr, "password isnt equals\n");
        sqlite3_finalize(pass);
        free(login);
        return 1;
    }
    free(login);
    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE user_data SET name = ?, password = ?, language = ? WHERE id = ?", -1, &edit_stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(edit_stmt, 1, new_name, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(edit_stmt, 2, crypt(new_password, "name"), -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(edit_stmt, 3, new_lang), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(edit_stmt, 4, user_id), result);
    if(sqlite3_step(edit_stmt) != SQLITE_DONE)
    {
        return sqlite3_step(edit_stmt);
    }
    sqlite3_finalize(pass);
    sqlite3_finalize(edit_stmt);
    return 0;
}
