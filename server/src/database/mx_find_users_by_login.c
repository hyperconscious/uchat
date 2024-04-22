#include "database.h"

char **mx_find_users_by_login(sqlite3 *db, uint8_t max_counts, const char *name, uint16_t *count) {
    char **users_array = NULL;
    *count = 0;
    sqlite3_stmt *statement;
    int rc = sqlite3_prepare_v2(db, 
                               "SELECT name FROM user_data "
                                "WHERE name LIKE '%' || ? || '%' "
                              //  "AND id NOT IN ("
                              //  "SELECT user_id FROM chat_participant"
                                //"GROUP BY user_id "
                             //   ");",
                                ,-1, &statement, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);

    uint16_t capacity = 10;
    users_array = malloc(capacity * sizeof(char *));
    if (!users_array) {
        fprintf(stderr, "Memory allocation failed\n");
        sqlite3_finalize(statement);
        return NULL;
    }
    while ((*count < max_counts) && (rc = sqlite3_step(statement)) == SQLITE_ROW) {
        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(users_array, capacity * sizeof(char *));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(users_array);
                sqlite3_finalize(statement);
                return NULL;
            }
            users_array = temp;
        }
        char *name = strdup((const char *)sqlite3_column_text(statement, 0));
        if (!name) {
            fprintf(stderr, "Memory allocation failed\n");
            free(users_array);
            sqlite3_finalize(statement);
            return NULL;
        }
        users_array[(*count)++] = name;
    }
    if (rc != SQLITE_DONE) {
         fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(db));
        for (uint16_t i = 0; i < *count; ++i) {
            free(users_array[i]);
        }
        free(users_array);
        sqlite3_finalize(statement);
        return NULL;
    }
    sqlite3_finalize(statement);
    return users_array;
}
