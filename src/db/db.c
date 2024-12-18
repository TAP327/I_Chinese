#include <stdio.h>
#include <string.h>
#include "include/db/db.h"


const TABLE_SCHEMA TABLE_NAMES[2] = {
    {
        .NAME = "word",
        .NUM_COLUMNS = 5,
        .COLUMN_NAMES = {"id", "pinyin", "definition", "level", "sentences"}
    },
    {
        .NAME = "sentence",
        .NUM_COLUMNS = 3,
        .COLUMN_NAMES = {"id", "chinese", "english"}
    }
};


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
    for (int8_t i = 0; i < 2; i++) {
        sqlite3_stmt *stmt;
        char sql[28] = {0};
        snprintf(sql, sizeof(sql), "PRAGMA table_info(%s)", TABLE_NAMES[i].NAME);
        printf("Validating table: %s, %d\n", TABLE_NAMES[i].NAME, i);
        int rc = sqlite3_prepare_v2(db_handle, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db_handle));
            return rc;
        }

        sqlite3_bind_text(stmt, 1, TABLE_NAMES[i].NAME, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Table '%s' exists but has no columns.\n", TABLE_NAMES[i].NAME);
        } else if (rc == SQLITE_ROW) {
            printf("Table '%s' exists and has columns.\n", TABLE_NAMES[i].NAME);
        } else {
            fprintf(stderr, "Failed to query table info: %s\n", sqlite3_errmsg(db_handle));
            return rc;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *column_name = (const char *)sqlite3_column_text(stmt, 1);
            int8_t valid = 0;

            for (int8_t column_num = 0; column_num < TABLE_NAMES[i].NUM_COLUMNS; column_num++) {
                if (strcmp(column_name, TABLE_NAMES[i].COLUMN_NAMES[column_num]) == 0) {
                    valid = 1;
                    break;
                }
            }

            if (!valid) {
                fprintf(stderr, "Invalid column: %s\n", column_name);
                return 1;
            }
        }
        sqlite3_finalize(stmt);
    }
    return SQLITE_OK;
}
