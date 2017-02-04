#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <sqlite3ext.h>

#include "orafn.h"

SQLITE_EXTENSION_INIT1

extern int sqlite3_extension_init(sqlite3                     *db,
                                  char                       **pzErrMsg,
                                  const sqlite3_api_routines  *pApi) {
  SQLITE_EXTENSION_INIT2(pApi)
  (void)setlocale(LC_ALL, "en_US.UTF-8");  
  sqlite3_create_function(db, "sin", 1, SQLITE_UTF8,
                          0, ora_sin, 0, 0);
  // -1 means variable number of arguments
  sqlite3_create_function(db, "lpad", -1, SQLITE_UTF8,
                          0, ora_lpad, 0, 0);
  sqlite3_create_function(db, "IF", 3, SQLITE_UTF8,
                          0, my_IF, 0, 0);
  sqlite3_create_function(db, "CONCAT", 2, SQLITE_UTF8,
                          0, ora_CONCAT, 0, 0);
  sqlite3_create_function(db, "TIME_TO_SEC", 1, SQLITE_UTF8,
                          0, my_TIME_TO_SEC, 0, 0);
  sqlite3_create_function(db, "REVERSE", 1, SQLITE_UTF8,
                          0, my_REVERSE, 0, 0);
  sqlite3_create_function(db, "INITCAP", 1, SQLITE_UTF8,
                          0, ora_INITCAP, 0, 0);
  sqlite3_create_function(db, "POW", 2, SQLITE_UTF8,
                          0, my_POW, 0, 0);
  return 0;
}
