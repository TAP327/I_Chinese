#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include <stdint.h>

#define MAX_COLUMNS 5

typedef const struct TABLE_SCHEMA {
    const char *NAME;
    const int NUM_COLUMNS;
    const char *COLUMN_NAMES[MAX_COLUMNS]; 
} TABLE_SCHEMA;

extern const TABLE_SCHEMA TABLE_NAMES[2];

sqlite3 *init_db_engine(char *db);
void close_db_engine(sqlite3 *db_handle);
int8_t validate_db(sqlite3 *db_handle);

#endif
