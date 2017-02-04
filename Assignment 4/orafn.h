#ifndef ORAFN_H

#define ORAFN_H

#include <sqlite3.h>

extern void ora_sin(sqlite3_context  *context,
                    int               argc,
                    sqlite3_value   **argv);
extern void ora_lpad(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void my_IF(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void ora_CONCAT(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void my_TIME_TO_SEC(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void my_REVERSE(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void ora_INITCAP(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);
extern void my_POW(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv);

#endif
