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
 *   INITCAP(string_to_be_formatted)
 *
 *   INITCAP makes the first letter of each word a capital letter, while making the rest of the words lowercase. Numbers and punctuation remain the same.
 *
 *   string_to_be_formatted represents the input string of characters that the user wishes to format. It is the only parameter.
 */
extern void ora_INITCAP(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv)
{
  int              len1;          //The number of characters in the string that is being passed in.
  unsigned char   *str1;          //The string being passed in.
  unsigned char   *strptr = NULL; //An additional pointer to str1.

  //Check to make sure that exactly one parameter was passed in.
  if (argc != 1)
  {
     sqlite3_result_error(context, "INITCAP - Invalid number of arguments (1 required).", -1);
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
     	sqlite3_result_error(context, "INITCAP - Please ensure that the input is a string of characters in the form 'string_to_be_formatted'", -1);
	return;
     }     
     
     //In this case, we know that we have valid input. We read in the input, and calculate the length of the string. We also assign an additonal pointer to the string for the purpose of formatting the string.
     str1 = (unsigned char *)sqlite3_value_text(argv[0]);
     strptr = str1;
     len1 = charlen(str1);
     int first; //This simply represents whether or not we are modifying the first letter of a word. It is 1 if so, and 0 if not. 

     //Now we need to go through the entire string to ensure proper formatting. This will make iniial characters uppercase, the other characters lowercase, and leave the other characters the same.
     while (strptr[0] != '\0')
     {       
        first = 1;
        if(!isalpha(*strptr))
        {
          strptr++;
        }
	while (isalpha(*strptr)) 
        {
           if (first == 1)
	   {
	      strptr[0] = (toupper(strptr[0]));
              strptr++;
              first = 0;
           }
           else
           {
              strptr[0] = tolower(strptr[0]);
              strptr++;
           }
        }
     } 
   }
   //The formatted string is then outputed to SQLite.
   sqlite3_result_text(context,
                      (char *)str1,
                      -1,            // Length - -1 means terminated by \0
                      NULL);         // Function for freeing memory
}
