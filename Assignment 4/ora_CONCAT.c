/*
 *  Author: Christian Hughes
 *  Certain code snippets authored by S Faroult (Used with permission)
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
//  Returns the length of s in CHARACTERS, not bytes.
//
static int charlen(unsigned char *s)
{
    int len = 0;
    unsigned char *p = s;

    while (*p != '\0') 
    {
       len++;
       // Beware that the macro increments p
       SQLITE_SKIP_UTF8(p);
    }
    return len;
}

/*
 *   CONCAT(string_part_1, string_part_2)
 *
 *   CONCAT combines two strings of characters together. It requires two parameters,
 *   both of which must be strings of characters. This function will not combine 
 *   numeric types.
 *
 *   string_part_1 represents the base string -- the string to be added on to.
 *
 *   string_part_2 represents the string to be added -- it will be placed at the end of string_part_1.
 */
extern void ora_CONCAT(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv)
{
  int              len1;   //number of characters in the 1st string
  int              len2;   //number of characters in the 2nd string
  unsigned char   *str1;   //The first string
  unsigned char   *str2;   //The second string
  unsigned char   *result; //The result string
  
  //Check to make sure that exactly two parameters were passed in.
  if (argc != 2)
  {
     sqlite3_result_error(context, "CONCAT - Invalid number of arguments (2 required).", -1);
  } 
  else 
  { 
     // Check whether at least one parameter is null. Outputs NULL if that is the case.
     if ((sqlite3_value_type(argv[0]) == SQLITE_NULL)
         || (sqlite3_value_type(argv[1]) == SQLITE_NULL)) {
        sqlite3_result_null(context);
        return;
     }

     // Make sure that both of the parameters that are passes in are character strings.    
     if (sqlite3_value_type(argv[0]) != SQLITE_TEXT || sqlite3_value_type(argv[1]) != SQLITE_TEXT)
     {
     	sqlite3_result_error(context, "CONCAT - Please ensure that both input parameters are strings of characters.", -1);
	return;
     }     

     //If the input is valid, then we can go ahead a perfrom the concatination as intended...
     //Get both of the user strings.
     str1 = (unsigned char *)sqlite3_value_text(argv[0]);
     str2 = (unsigned char *)sqlite3_value_text(argv[1]);

     //Use the charlen to get the length of each string in CHARACTERS.
     len1 = charlen(str1);
     len2 = charlen(str2);

     //Allocate enough memory for the combined string (maximum of 4 bytes per character, plus one byte for the '\0' character)
     if ((result = (unsigned char *)sqlite3_malloc((len1 * 4) + (len2 * 4) + 1)) == NULL) 
     {
        // Don't even try to check what goes wrong ...
        // Rats leaving ship.
        sqlite3_result_null(context);
        return;
     }

     //Use the following two fuctions to actually combine the strings.
     strcpy(result, str1);
     strcat(result, str2);
   }

   //Return the concatanated string.  
   sqlite3_result_text(context,
                      (char *)result,
                      -1,            // Length - -1 means terminated by \0
                      sqlite3_free); // Function for freeing memory
}
