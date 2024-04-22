#include "database.h"

void mx_test_db_add_user(void)
{
    fprintf(stderr, "\nAdd user to db test...\n");
    sqlite3_stmt *stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_add_user(db, &stmt);
    int status = mx_add_user(stmt, "test user2", "1234", 0);
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
    long id = mx_get_user_id_by_login(get_user_stmt, "test user2");
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

void mx_test_db_add_user_to_chat(void)
{
    fprintf(stderr, "\nAdd user to chat db test...\n");
    sqlite3_stmt *add_stmt;
    sqlite3_stmt *get_user_stmt;
    sqlite3_stmt *get_chat_stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_add_user_to_chat(db, &add_stmt);
    mx_init_find_id_by_user(db, &get_user_stmt);
    mx_init_get_chats_by_name(db, &get_chat_stmt);
    t_db_chat *chats;
    uint16_t count;
    
    long id = mx_get_user_id_by_login(get_user_stmt, "test user2");
    if(id == -1)
    {
        sqlite3_close(db);
        fprintf(stderr, "Test failed, cannot find user\n");
        return;
    }
    mx_get_chats_by_name(get_chat_stmt, "test chat", -1, &chats, &count);
    fprintf(stderr, "user id = %ld, chat id = %ld\n", id, chats[0].id);
    mx_add_user_to_chat(add_stmt, id, chats[0].id);
    fprintf(stderr, "Test passed\n");
    free(chats);
    sqlite3_finalize(get_user_stmt);
    sqlite3_finalize(get_chat_stmt);
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
    long id = mx_get_user_id_by_login(get_id_stmt, "test user2");
    if(mx_add_chat(stmt, "test chat", id))
        fprintf(stderr, "Test failed\n");
    else    
        fprintf(stderr, "Test passed\n");
    sqlite3_finalize(stmt);
    sqlite3_finalize(get_id_stmt);
    sqlite3_close(db);
}

void mx_test_db_get_users_from_chat(void)
{
    fprintf(stderr, "\nGet users from chat test...\n");
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    sqlite3_stmt *get_chats_stmt;
    mx_init_get_chats_by_name(db, &get_chats_stmt);
    t_db_chat *chats;
    uint16_t chats_count;
    uint32_t *ids;

    mx_get_chats_by_name(get_chats_stmt, "test_chat", -1, &chats, &chats_count);

    uint16_t users_count;
    mx_get_users_from_chat(db, chats[0].id, -1, &ids,  &users_count);
    
}

void mx_test_db_remove_chat(void)
{
    fprintf(stderr, "\nRemove chat from db test...\n");
    sqlite3_stmt *remove_stmt;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_init_sub_chat(db, &remove_stmt);
    
    sqlite3_stmt *get_chat_stmt;

    mx_init_get_chats_by_name(db, &get_chat_stmt);

    t_db_chat *chats;
    uint16_t chats_count;
    if(mx_get_chats_by_name(get_chat_stmt, "test chat", 1, &chats, &chats_count))
    {
        fprintf(stderr, "error\n");
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
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
    mx_test_db_add_user_to_chat();
    //mx_test_db_remove_chat();
    //mx_test_db_remove_user();
    fprintf(stderr, "\nTests finished\n");
}

