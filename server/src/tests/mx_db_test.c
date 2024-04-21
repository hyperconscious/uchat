#include "database.h"

void mx_test_db_add_user(void)
{
    fprintf(stderr, "\nAdd user to db test...\n");
    sqlite3_stmt *stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_add_user(db, &stmt);
    int status = mx_add_user(stmt, "test user", "1234");
    int id;
    id = sqlite3_last_insert_rowid(db);
    if(status != SQLITE_OK)
    {
        fprintf(stderr, "User dont added %d\n", status);
        if(status == SQLITE_CONSTRAINT)
            fprintf(stderr, "User with same login already exists\n");
    }
    else
        fprintf(stderr, "Add user with id %d, test passed\n", id);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mx_test_db_remove_user(void)
{
    fprintf(stderr, "\nRemove user from db test...\n");
    sqlite3_stmt *remove_stmt;
    sqlite3_stmt *get_user_stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_sub_user(db, &remove_stmt);
    mx_init_find_id_by_user(db, &get_user_stmt);
    long id = mx_get_user_id_by_login(get_user_stmt, "test user");
    if(id == -1)
    {
        sqlite3_close(db);
        fprintf(stderr, "Test failed, cannot find user\n");
        return;
    }
    int status = mx_sub_user(remove_stmt, id);

    if(status != SQLITE_OK)
    {
        fprintf(stderr, "User dont Removed %d\n", status);
    }
    else
        fprintf(stderr, "Remove user test passed\n");
    sqlite3_finalize(remove_stmt);
    sqlite3_finalize(get_user_stmt);
    sqlite3_close(db);
}

void mx_test_db_add_chat(void)
{
    fprintf(stderr, "\nAdd chat to db test...\n");
    sqlite3_stmt *stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_add_chat(db, &stmt);
    
    sqlite3_stmt *get_id_stmt;

    mx_init_find_id_by_user(db, &get_id_stmt);
    long id = mx_get_user_id_by_login(get_id_stmt, "test user");
    if(mx_add_chat(stmt, "test chat", id))
        fprintf(stderr, "Test failed\n");
    else    
        fprintf(stderr, "Test passed\n");
    sqlite3_finalize(stmt);
    sqlite3_finalize(get_id_stmt);
    sqlite3_close(db);
}

void mx_test_db_remove_chat(void)
{
    fprintf(stderr, "\nRemove chat from db test...\n");
    sqlite3_stmt *remove_stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_sub_chat(db, &remove_stmt);
    
    sqlite3_stmt *get_chat_stmt;

    mx_init_get_chats_id_by_name(db, &get_chat_stmt);

    t_chat *chats;
    int chats_count;
    if(mx_get_chats_by_name(get_chat_stmt, "test chat", 1, &chats, &chats_count))
    {
        fprintf(stderr, "error\n");
        sqlite3_finalize(remove_stmt);
        sqlite3_finalize(get_chat_stmt);
        sqlite3_close(db);
        return;
    }

    if(mx_sub_chat(remove_stmt, chats[0].id))
        fprintf(stderr, "Test failed\n");
    else
        fprintf(stderr, "Test passed\n");
    sqlite3_finalize(remove_stmt);
    sqlite3_finalize(get_chat_stmt);
    sqlite3_close(db);
}

void mx_test_db_all(void)
{
    mx_test_db_add_user();
    mx_test_db_add_chat();
    mx_test_db_remove_chat();
    mx_test_db_remove_user();
    fprintf(stderr, "\nTests finished\n");
}

