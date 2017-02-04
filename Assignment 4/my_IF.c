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

/*
 *   IF(expression, string_or_number_if_true, string_or_number_if_false)
 *
 *   The IF() fuction takes three parameters. If the first parameter evaluates to true,
 *   then the second parameter is printed. If the first paramter is false, then the third 
 *   parameter is printed.
 *   
 *   expression refers to the expression that the user would like to be evaluated -- MUST EVALUATE TO A BOOLAN.
 *
 *   string_or_number_if_true is an integer or a string that will be printed if the expression is true.
 *
 *   string_or_number_if_false is an integer or a string that will be printed if the expression is false.
 */
extern void my_IF(sqlite3_context  *context,
                    int               argc,
                    sqlite3_value   **argv)
{
  char *yesIfString;
  char *noIfString;
  int yesIfInt;
  int noIfInt;
  int state;
  
  //Check to make sure that exactly thee parameters were passed in.
  if (argc != 3)
  {
     sqlite3_result_error(context, "IF - Invalid number of arguments (3 required).", -1);
  } 
  else 
  { 
     // Check whether at least one parameter is null. Outputs NULL if that is the case.
     if ((sqlite3_value_type(argv[0]) == SQLITE_NULL)
         || (sqlite3_value_type(argv[1]) == SQLITE_NULL) || (sqlite3_value_type(argv[2])) == SQLITE_NULL) {
        sqlite3_result_null(context);
        return;
     }

     //Ensure that the second and third parameters are either strings, or integers.  
     if ((sqlite3_value_type(argv[1]) == SQLITE_TEXT || sqlite3_value_type(argv[1]) == SQLITE_INTEGER) && (sqlite3_value_type(argv[2]) == SQLITE_TEXT || sqlite3_value_type(argv[2]) == SQLITE_INTEGER))
     {
         //Figure out what the expression evaluates to (true or false).
         state = sqlite3_value_int(argv[0]);
         
         //If the expression is true, print out the second parameter dependent on its data type. Similar if false, but for the third parameter.
         if(state == 1)
         {
  	     if (sqlite3_value_type(argv[1]) == SQLITE_TEXT)
             {
                yesIfString = (char *)sqlite3_value_text(argv[1]);
                sqlite3_result_text(context, yesIfString, -1, NULL);
	        return;
             }
             else
             {
                yesIfInt = sqlite3_value_int(argv[1]);
                sqlite3_result_int(context, yesIfInt);
                return;
             }
         }
         else
         {
	     if (sqlite3_value_type(argv[2]) == SQLITE_TEXT)
             {
                 noIfString = (char *)sqlite3_value_text(argv[2]);
                 sqlite3_result_text(context, noIfString, -1, NULL);
	         return;
             }
             else
             {
                 noIfInt = sqlite3_value_int(argv[2]);
                 sqlite3_result_int(context, noIfInt);
                 return;
             }
         }
     }
     else
     {
        sqlite3_result_error(context, "IF - Please ensure that input is in the from IF(expression, string_or_number_if_true, string_or_number_if_false).", -1);
	return;
     }   
  }
 
}



mysql pow()
