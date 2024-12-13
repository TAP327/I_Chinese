#include <stdio.h>
#include "include/db/db.h"

sqlite3 *init_db_engine(char *db) {
    sqlite3 *db_handle;
    int8_t sql_error = 0;
    sql_error = sqlite3_open(db, &db_handle);

    if (sql_error) {
        fprintf(stderr, "Error opening DB: %s\n", sqlite3_errmsg(db_handle));
        sqlite3_close(db_handle);
    }

    return db_handle;
}

void close_db_engine(sqlite3 *db_handle) {
    if (db_handle) {
        sqlite3_close(db_handle);
        printf("Cleanign up db");
    }
}
