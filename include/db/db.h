#ifndef __DB_H
#define __DB_H

#include <sqlite3.h>
#include <stdint.h>

sqlite3 *init_db_engine(char *db);
void close_db_engine(sqlite3 *db_handle);

#endif
