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
        printf("Cleaning up db...\n");
    }
}

int8_t validate_db(sqlite3 *db_handle) {
    sqlite3_stmt *stmt;
    const char *sql = "PRAGMA table_info(word)";
    int rc = sqlite3_prepare_v2(db_handle, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db_handle));
        return rc;
    }

    const char *table_name = "word";
    sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Table '%s' exists but has no columns.\n", table_name);
    } else if (rc == SQLITE_ROW) {
        printf("Table '%s' exists and has columns.\n", table_name);
    } else {
        fprintf(stderr, "Failed to query table info: %s\n", sqlite3_errmsg(db_handle));
        return rc;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *column_name = (const char *)sqlite3_column_text(stmt, 1);
        printf("Column: %s\n", column_name);  // Print each column in the table
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}
