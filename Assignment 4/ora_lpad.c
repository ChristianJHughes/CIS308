/*
 *  Written by S Faroult
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sqlite3.h>

#ifndef SQLITE_SKIP_UTF8
// Macro copied from the sqlite code
#define SQLITE_SKIP_UTF8(zIn) {                        \
      if( (*(zIn++))>=0xc0 ){                              \
              while( (*zIn & 0xc0)==0x80 ){ zIn++; }             \
            }                                                    \
}

#endif

//
//  Returns the length of s in CHARACTERS, not bytes
//
static int charlen(unsigned char *s) {
    int            len = 0;
    unsigned char *p = s;

    while (*p != '\0') {
       len++;
       // Beware that the macro increments p
       SQLITE_SKIP_UTF8(p);
    }
    return len;
}

/*
 *   LPAD( string, padded_length, [ pad_string ] )
 *
 *   Left pads "string" to "padded length" characters (not bytes),
 *   with spaces by default, or 'pad_string' otherwise
 *
 *   string is the string to pad characters to (the left-hand side).
 *
 *   padded_length is the number of characters to return.
 *   If the padded_length is smaller than the original string, the LPAD
 *   function will truncate the string to the size of padded_length.
 *
 *   pad_string is optional. This is the string that will be padded to
 *   the left-hand side of string. If this parameter is omitted, the LPAD
 *   function will pad spaces to the left-side of string.
 */
extern void ora_lpad(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv){
  int              len;    // Required length
  int              clen;   // number of CHARACTERS in the string
  unsigned char   *str;   
  unsigned char   *pad;
  unsigned char   *result;
  unsigned char   *r;
  unsigned char   *p;
  int              padlen; // CHARACTER length of padding
  int              i;

  if ((argc < 2) || (argc > 3)){
     sqlite3_result_error(context, "lpad - invalid number of arguments", -1);
  } else { 
     // Check whether at least one parameter is null
     if ((sqlite3_value_type(argv[0]) == SQLITE_NULL)
         || (sqlite3_value_type(argv[1]) == SQLITE_NULL)) {
        sqlite3_result_null(context);
        return;
     }
     // Check whether the length is a positive value
     if ((sqlite3_value_numeric_type(argv[1]) != SQLITE_INTEGER)
         || ((len = sqlite3_value_int(argv[1])) <= 0)) {
        sqlite3_result_error(context, "lpad - invalid length", -1);
        return;
     }
     str = (unsigned char *)sqlite3_value_text(argv[0]);
     if (argc == 2) {
        // Default padding
        pad = (unsigned char *)" ";
        padlen = 1;
     } else {
        // Padding with null returns null
        if (sqlite3_value_type(argv[2]) == SQLITE_NULL) {
           sqlite3_result_null(context);
           return;
        }
        pad = (unsigned char *)sqlite3_value_text(argv[2]);
        padlen = charlen(pad);
     }
     // Allocate memory for 4 * required length (as a character
     // is at most four bytes), plus one for \0
     if ((result = (unsigned char *)sqlite3_malloc(4 * len + 1)) == NULL) {
        // Don't even try to check what goes wrong ...
        // Rats leaving ship.
        sqlite3_result_null(context);
        return;
     }
     // Check the length of the original string
     clen = charlen(str);
     // Copy - i is a CHARACTER counter
     r = result;
     p = pad;
     i = 0;
     // First insert padding (if required length
     // is greater than string length)
     while (i < len - clen) {
        i++;
        *r = *p;
        r++;
        if ((*(p++))>=0xc0 ){
           while((*p & 0xc0)==0x80){
              *r = *p;
              p++;
              r++;
           }
        }
        // Check whether we must repeat the padding
        if (*p == '\0') {
           p = pad;
        }
     }
     // Now add the string
     p = str;
     while (i < len) {
        i++;
        *r = *p;
        r++;
        if ((*(p++))>=0xc0 ){
           while((*p & 0xc0)==0x80){
              *r = *p;
              p++;
              r++;
           }
        }
     }
     *r = '\0';
  }
  sqlite3_result_text(context,
                      (char *)result,
                      -1,            // Length - -1 means terminated by \0
                      sqlite3_free); // Function for freeing memory

}
