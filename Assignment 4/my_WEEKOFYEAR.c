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
 *   TIME_TO_SEC(time_to_be_converted)
 *
 *   TIME_TO_SEC converts a time (MUST BE IN 'hh:mm:ss' FORMAT) into it's equivlent number of seconds. 
 *   The seconds are returned as an integer.
 *
 *   time_to_be_converted refers to the time that the user wishes to be converted into seconds.
 *   It must be in the format 'hh:mm:ss'.
 */
extern void my_WEEKOFYEAR(sqlite3_context  *context,
                     int               argc,
                     sqlite3_value   **argv)
{
  int              len1;   //number of characters in the 1st string
  unsigned char   *str1;   //The first string
  int             result;  //The result string (numeric number of seconds)
  
  //Check to make sure that exactly one parameter is passed in.
  if (argc != 1)
  {
     sqlite3_result_error(context, "TIME_TO_SEC - Invalid number of arguments (1 required).", -1);
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
     	sqlite3_result_error(context, "TIME_TO_SEC - Please ensure that the input is a string of characters in the form 'hh:mm:ss'", -1);
	return;
     }     
     // Make sure that the input that is passed in is in TIME format ('hh:mm:ss').
     // First check to see if it is EIGHT characters long
     str1 = (unsigned char *)sqlite3_value_text(argv[0]);
     len1 = charlen(str1);
     if (len1 != 8)
     {
	sqlite3_result_error(context, "TIME_TO_SEC - Please ensure that the input is a string of characters in the form 'hh:mm:ss'", -1);
	return;
     }
     //If it is the correct number of characters, we must check to make sure that the formating is correct 'hh:mm:ss'.
     int i;
     for (i = 0; i < len1; i++)
     {
     	if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7)
        {
          if (!isdigit(str1[i]))
	  {
	    sqlite3_result_error(context, "TIME_TO_SEC - Please ensure that the input is a string of characters in the form 'hh:mm:ss'", -1);
	    return;
	  }
   	}
	else
        {
          if (!(str1[i] == ':'))
	  {
	    sqlite3_result_error(context, "TIME_TO_SEC - Please ensure that the input is a string of characters in the form 'hh:mm:ss'", -1);
	    return;	
	  }
        }
     }
     
     //WE KNOW THAT THE INPUT IS VALID. Time to parse out the hours/minutes/seconds.
     char hr[2];
     char min[2];
     char sec[2];
     hr[0] = str1[0];
     hr[1] = str1[1];
     min[0] = str1[3];
     min[1] = str1[4];
     sec[0] = str1[5];
     sec[1] = str1[1];
     int hours = atoi(hr); 
     int minutes = atoi(min); 
     int seconds = atoi(sec);
     
     //Calculate the number of seconds based on the given input.
     result = (hours * 3600) + (minutes * 60) + seconds;
   }
  //Print the number of seconds as an integer. 
  sqlite3_result_int(context, result);
}
