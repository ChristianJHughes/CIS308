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
#include <math.h>

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
 *   REVERSE(string_To_Be_Reversed)
 *
 *   Reverse takes a string of characters, and returns the reverse of this string. It only takes one parameter.
 *
 *   string_to_be_reversed represents the input string that the user wishes to reverse. It is the only parameter.
 */
extern void my_REVERSE(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv)
{
  int              len1;   //The number of characters in the string that is being passed in.
  unsigned char   *str1;   //The string being passed in.
  
  //Check to make sure that exactly one parameter was passed in.
  if (argc != 1)
  {
     sqlite3_result_error(context, "REVERSE - Invalid number of arguments (1 required).", -1);
  } 
  else 
  { 
     // Check whether the parameter is null. Outputs NULL if that is the case.
     if (sqlite3_value_type(argv[0]) == SQLITE_NULL) 
     {
        sqlite3_result_null(context);
        return;
     }

     // Make sure that the parameter is a string of characters.    
     if (sqlite3_value_type(argv[0]) != SQLITE_TEXT)
     {
     	sqlite3_result_error(context, "REVERSE - Please ensure that the input is a string of characters in the form 'string_to_be_reversed'", -1);
	return;
     }     
     
     //In this case, we know that we have valid input. We read in the input, and calculate the length of the string.
     str1 = (unsigned char *)sqlite3_value_text(argv[0]);
     len1 = charlen(str1);
     
     //Time to reverse the string! A temporary character/counters are created. The original string will end up reversed.
     int back = len1 - 1;
     int front = 0;
     char letter;
     while (front < back)
     {
	letter = str1[front];
	str1[front] = str1[back];
	str1[back] = letter;
	front++; 
	back--;
     }
     
   }
   //The reversed string is then outputed to SQLite.
   sqlite3_result_text(context,
                      (char *)str1,
                      -1,            // Length - -1 means terminated by \0
                      NULL);         // Function for freeing memory
}
