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

/*
 *   POW(base_of_exponetiation, exponent_of_exponentiation)
 *  
 *   POW() takes two parameters (listed above) and returns the value of a number raised
 *   to the power of another number. 
 *
 *   base_of_exponetation refers the base that will be acted upon by the exponent -- MUST BE A DOUBLE.
 *
 *   exponent_of_exponentiation represents the exponent that will be working on the base.
 */
extern void my_POW(sqlite3_context  *context,
                    int               argc,
                    sqlite3_value   **argv){
  double        base;
  double        exponent;
  char         *v;
  char         *v2;

  //Ensure that exactly two parameters have been passed to the function.
  if (argc != 2)
  {
     sqlite3_result_error(context, "POW - Invalid number of arguments (2 required).", -1);
     return;
  } 
  // Check whether the value is actually a number. Alert the user or return null otherwise.
  v = (char *)sqlite3_value_text(argv[0]);
  v2 =(char *)sqlite3_value_text(argv[1]);
  if (v == NULL){
     sqlite3_result_null(context);
  } else {
     if (sscanf(v, "%lf", &base) == 1 && sscanf(v2, "%lf", &exponent) == 1)
     {
        //Both parameters are valid input. We can now compute the result acurately. 
        base = sqlite3_value_double(argv[0]);
        exponent = sqlite3_value_double(argv[1]);
        sqlite3_result_double(context, pow(base, exponent));
     } else {
        // Wrong input
        sqlite3_result_error(context, "Invalid numerical value. Both parameters must be valid doubles.", -1);
     }
  }
}
