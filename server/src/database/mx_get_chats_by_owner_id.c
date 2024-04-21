#include "database.h"

char **mx_get_chat_names(sqlite3 *db, int owner_id, uint16_t *count) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT name FROM chat WHERE owner_id = ?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, owner_id);

    *count = 0;
    char **chat_names = NULL;

    uint16_t capacity = 15;
    chat_names = malloc(capacity * sizeof(char*));

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        char *name = strdup((char*)sqlite3_column_text(stmt, 0));
        if(*count >= capacity) {
            char **temp = realloc(chat_names, capacity * sizeof(char*));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(chat_names);
                return NULL;
            }
            chat_names = temp;
        }
        strcpy(chat_names[*count], name);
        (*count)++;
    }

    sqlite3_finalize(stmt);
    return chat_names;
}
