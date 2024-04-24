#include "../inc/database.h"

int mx_recreate_tables(sqlite3 *db)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS user_data", NULL, NULL, NULL), result);
    MX_TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS message", NULL, NULL, NULL), result);
    MX_TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS chat", NULL, NULL, NULL), result);
    MX_TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS chat_participant", NULL, NULL, NULL), result);

    MX_TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE user_data (\
        id	INTEGER,\
        name	TEXT UNIQUE NOT NULL,\
        password	TEXT, \
        language INTEGER NOT NULL,\
        PRIMARY KEY(id AUTOINCREMENT)\
    );", NULL, NULL, NULL), result);

    MX_TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE chat (\
        id 	INTEGER UNIQUE,\
        name	TEXT NOT NULL,\
        owner_id	INTEGER,\
        creation_time DATETIME,\
        is_private BOOLEAN DEFAULT 0,\
        PRIMARY KEY(id AUTOINCREMENT),\
        FOREIGN KEY(owner_id) REFERENCES user_data(id)\
    );", NULL, NULL, NULL), result);

    MX_TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE chat_participant (\
        id	INTEGER UNIQUE, \
        user_id	INTEGER, \
        chat_id	INTEGER, \
        last_readed_message_id INTEGER DEFAULT -1, \
        PRIMARY KEY(id AUTOINCREMENT), \
        FOREIGN KEY(user_id) REFERENCES user_data(id), \
        FOREIGN KEY(chat_id) REFERENCES chat(id),\
        FOREIGN KEY(last_readed_message_id) REFERENCES message(id),\
        UNIQUE(user_id, chat_id)\
    );", NULL, NULL, NULL), result);

    MX_TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE message (\
        id	INTEGER,\
        time	DATETIME,\
        user_id	INTEGER,\
        chat_id	INTEGER,\
        text	TEXT, \
        PRIMARY KEY(id AUTOINCREMENT), \
        FOREIGN KEY(user_id) REFERENCES user_data(id),\
        FOREIGN KEY(chat_id) REFERENCES chat(id)\
    );", NULL, NULL, NULL), result);
    
    return 0;
}
