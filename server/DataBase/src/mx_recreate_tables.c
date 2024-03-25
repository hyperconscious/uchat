#include "../inc/database.h"

int mx_recreate_tables(sqlite3 *db)
{
    int result = 0;
    TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS user_data", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS message", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS chat", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "DROP TABLE IF EXISTS chat_participant", NULL, NULL, NULL), result);

    TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE \"chat\" (\"id\"	INTEGER UNIQUE,\"name\"	TEXT NOT NULL,\"owner_id\"	INTEGER,PRIMARY KEY(\"id\" AUTOINCREMENT),FOREIGN KEY(\"owner_id\") REFERENCES \"group_chat\"(\"id\"));", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE \"chat_participant\" (\"user_id\"	INTEGER UNIQUE, \"chat_id\"	INTEGER UNIQUE, FOREIGN KEY(\"user_id\") REFERENCES \"user_data\"(\"id\"), FOREIGN KEY(\"chat_id\") REFERENCES \"chat\"(\"id\"));", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE \"message\" (\"id\"	INTEGER,\"time\"	REAL,\"user_id\"	INTEGER,\"chat_id\"	INTEGER,\"text\"	TEXT,PRIMARY KEY(\"time\"),FOREIGN KEY(\"user_id\") REFERENCES \"user_data\"(\"id\"),FOREIGN KEY(\"chat_id\") REFERENCES \"chat\");", NULL, NULL, NULL), result);
    TRY_FUNCTION(sqlite3_exec(db, "CREATE TABLE \"user_data\" (\"id\"	INTEGER,\"name\"	TEXT NOT NULL,\"password\"	TEXT,PRIMARY KEY(\"id\" AUTOINCREMENT));", NULL, NULL, NULL), result);
    return 0;
}
