#include "inc/database.h"

int select_callback(void *transit, int count, char **columns, char **column_names)
{
    for(int i = 0; i < count; i++)
    {
        printf("%s : %s", columns[i], column_names[i]);   
    }
    return 0;
}

int main()
{
    t_db_info *info;
    if(!mx_init_db_info("Messanger.db", &info)) printf("DB info initialited correct\n");
    else printf("%s",sqlite3_errmsg(info->database));

    //if(!mx_recreate_tables(info->database)) printf("Tables created correct\n");
    //else printf("%s",sqlite3_errmsg(info->database));
    
    int id;
    if(!mx_add_user(info, "Vasya", "1234", &id)) printf("User added correct\n");

    if(!mx_sub_user(info, id)) printf("User removed correct\n");

    //sqlite3_exec(db, "SELECT * FROM user_data", select_callback, 0, 0);
    if(!mx_destroy_db_info(&info)) printf("DB info destroyed correct\n");

    return 0;
}
