#include <criterion/criterion.h>
#include <stdbool.h>
#include "include/db/db.h"

sqlite3 *db_handle = NULL;

void db_setup(void) {
    db_handle = init_db_engine("./assets/i_chinese.db");
}

void db_teardown(void) {
    close_db_engine(db_handle);
}

TestSuite(db_loader_suite, .init=db_setup, .fini=db_teardown);

Test(db_loader_suite, init_engine) {
    cr_expect(db_handle != NULL, "db_handle should not be null");
}

Test(db_loader_suite, validate_schema) {
    cr_expect(validate_db(db_handle) == SQLITE_OK, "Invalid DB schema");
}
