#include "database.h"

int *mx_find_users_by_login(sqlite3 *db, const char *name, uint16_t *count) {
    int *users_array = NULL;
    *count = 0;
    sqlite3_stmt *statement;
    int rc = sqlite3_prepare_v2(db, "SELECT id FROM user_data WHERE name LIKE '%' || ? || '%'", -1, &statement, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);

    uint16_t capacity = 10;
    users_array = malloc(capacity * sizeof(int));
    if (!users_array) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        if (*count >= capacity) {
            capacity *= 2;
            int *temp = realloc(users_array, capacity * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(users_array);
                return NULL;
            }
            users_array = temp;
        }
        users_array[(*count)++] = sqlite3_column_int(statement, 0);
    }
    if (rc != SQLITE_DONE) {
       fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(db));
       free(users_array);
    }
    sqlite3_finalize(statement);
    return users_array;
}
