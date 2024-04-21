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
        if(*count >= capacity) {
            char **temp = realloc(chat_names, capacity * sizeof(char*));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed\n");
                for (uint16_t i = 0; i < *count; ++i) {
                    free(chat_names[i]);
                }
                free(chat_names);
                sqlite3_finalize(stmt);
                return NULL;
            }
            chat_names = temp;
        }
        const char *name = (const char*)sqlite3_column_text(stmt, 0);
        chat_names[*count] = strdup(name);
        (*count)++;
    }

    sqlite3_finalize(stmt);
    return chat_names;
}
