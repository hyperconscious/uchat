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
    sqlite3_finalize(add_stmt);
    sqlite3_finalize(get_user_stmt);
    sqlite3_finalize(get_chat_stmt);
    sqlite3_close(db);
}

void mx_test_db_message(void)
{
    fprintf(stderr, "\nmessaging db test...\n");
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    sqlite3_stmt *add_usr_stmt;
    sqlite3_stmt *add_chat_stmt;
    sqlite3_stmt *add_msg_stmt;
    sqlite3_stmt *get_usr_by_login;
    sqlite3_stmt *get_chat;
    sqlite3_stmt *add_usr_to_chat;
    mx_init_add_user(db, &add_usr_stmt);
    mx_init_add_chat(db, &add_chat_stmt);
    mx_init_add_message(db, &add_msg_stmt);
    mx_init_find_id_by_user(db, &get_usr_by_login);
    mx_init_get_chats_by_name(db, &get_chat);
    mx_init_add_user_to_chat(db, &add_usr_to_chat);

    if(mx_add_user(add_usr_stmt, "test_user1", "1234", 0))
    {
        fprintf(stderr, "Add user error\n");
    }
    uint32_t first_id = mx_get_user_id_by_login(get_usr_by_login, "test_user1");

    if(mx_add_user(add_usr_stmt, "test_user2", "2134", 0))
    {
        fprintf(stderr, "Add user error\n");
    }
    uint32_t second_id = mx_get_user_id_by_login(get_usr_by_login, "test_user2");

    if(mx_add_chat(add_chat_stmt, "stupid_chat", mx_get_user_id_by_login(get_usr_by_login, "test_user1"), 0))
    {
        fprintf(stderr, "Add chat error\n");
    }

    t_db_chat *chats;
    uint16_t chat_count;
    if(mx_get_chats_by_name(get_chat, "clever_chat", 1, &chats, &chat_count))
    {
        fprintf(stderr, "Get chats error\n");
    }
    uint32_t chat_id = chats[0].id;

    if( mx_add_user_to_chat(add_usr_to_chat, first_id, chat_id) ||
        mx_add_user_to_chat(add_usr_to_chat, second_id, chat_id))
    {
        fprintf(stderr, "Add user to chat error\n");
    }

    if( mx_add_message(add_msg_stmt, "Hello youuu", first_id, chat_id) ||
        mx_add_message(add_msg_stmt, "Hello you toooo", second_id, chat_id))
    {
        //fprintf(stderr, "%s\n%s\n", sqlite3_errstr(mx_add_message(add_msg_stmt, "Fuck youuu", first_id, chat_id)), sqlite3_errstr(mx_add_message(add_msg_stmt, "Fuck you toooo", second_id, chat_id)));
        fprintf(stderr, "Add message error %d %d %d\n", first_id, second_id, chat_id);
    }

    t_db_message *last_messages;
    int msg_count;
    if( mx_get_last_messages(db, chat_id, "", -1, &last_messages, &msg_count))
    {
        fprintf(stderr, "Get last messages error\n");
    }
    for(int i = 0; i < msg_count; i++)
    {
        char *login = mx_get_login_by_id(db, last_messages[i].user_id);
        fprintf(stderr, "user %d %s: printed \"%s\" at %s\n", last_messages[i].user_id, login, last_messages[i].text, last_messages[i].time);
        free(login);
    }
    if(mx_set_read_to_all_unread_messages(db, last_messages[0].user_id, chat_id))
    {
        fprintf(stderr, "Set read messages error %d %d %d\n", last_messages[0].user_id, chat_id, mx_set_read_to_all_unread_messages(db, last_messages[0].user_id, chat_id));
    }
    int stat = mx_edit_user(db, last_messages[0].user_id, "Nya nya cat", "12345", "nya1234", 2);
    if(stat)
    {
        fprintf(stderr, "Error at edit user\n");
        if(stat == SQLITE_CONSTRAINT)
            fprintf(stderr, "Because Nya nya cat was exited :3\n");
    }
    mx_edit_message(db, last_messages[0].id, "hi :3");
    mx_add_message(add_msg_stmt, "New message1", first_id, chat_id);
    mx_add_message(add_msg_stmt, "New message2", first_id, chat_id);
    mx_add_message(add_msg_stmt, "New message3", first_id, chat_id);
    // if(mx_get_unread_messages(db, last_messages[0].user_id, chat_id, &last_messages, &msg_count))
    // {
    //     fprintf(stderr, "Get last messages error\n");
    // }
    if( mx_get_last_messages(db, chat_id, "", -1, &last_messages, &msg_count))
    {
        fprintf(stderr, "Get last messages error\n");
    }
    for(int i = 0; i < msg_count; i++)
    {
        fprintf(stderr, "user %d %s: printed \"%s\" at %s\n", last_messages[i].user_id, mx_get_login_by_id(db, last_messages[i].user_id), last_messages[i].text, last_messages[i].time);
    }

    mx_sub_chat(db, chats[0].id);
    sqlite3_stmt *rem_user_stmt;
    mx_init_sub_user(db, &rem_user_stmt);
    mx_sub_user(rem_user_stmt, mx_get_user_id_by_login(get_usr_by_login, "Nya nya cat"));
    sqlite3_finalize(rem_user_stmt);
    
    sqlite3_finalize(add_usr_stmt);
    sqlite3_finalize(add_chat_stmt);
    sqlite3_finalize(add_msg_stmt);
    sqlite3_finalize(get_usr_by_login);
    sqlite3_finalize(get_chat);
    
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
    if(mx_add_chat(stmt, "test chat", id, 0))
        fprintf(stderr, "Test failed %d\n", mx_add_chat(stmt, "test chat", id, 0));
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
    sqlite3_finalize(get_chats_stmt);
    sqlite3_close(db);
}

void mx_test_db_remove_chat(void)
{
    fprintf(stderr, "\nRemove chat from db test...\n");
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    
    sqlite3_stmt *get_chat_stmt;

    mx_init_get_chats_by_name(db, &get_chat_stmt);

    t_db_chat *chats;
    uint16_t chats_count;
    
    if(mx_get_chats_by_name(get_chat_stmt, "test chat", 1, &chats, &chats_count))
    {
        fprintf(stderr, "error\n");
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(get_chat_stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(get_chat_stmt);
    if(mx_sub_chat(db, chats[0].id) != SQLITE_OK)
        fprintf(stderr, "Test failed %d\n", mx_sub_chat(db, chats[0].id));
    else
        fprintf(stderr, "Test passed\n");
    sqlite3_finalize(get_chat_stmt);
    sqlite3_close(db);
}

void mx_test_db_all(void)
{
    mx_test_db_add_user();
    mx_test_db_add_chat();
    //mx_test_db_add_user_to_chat();
    mx_test_db_message();
    mx_test_db_remove_chat();
    mx_test_db_remove_user();
    fprintf(stderr, "\nTests finished\n");
}

