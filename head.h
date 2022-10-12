#ifndef HEAD
#define HEAD	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "global_var.h"
#include "constants.h"


#define BASE 10
#define check_if_memory_allocated(var) \
    if(!(var)) { \
        printf("Error: couldn't allocate memory. exit program\n"); \
        exit(0); \
    }

typedef enum bool {
    false,
    true
} bool;


/**
* This method prints an error
* @param lineNum the number of the line in which the error occured
* @param ErrorFormat the format of the error using standart c formatting, followed by the variable to be put in the format
* @return if the line passed is -1 then the function reset the counter and returns if there was any errors, otherwise it returns true
*/
bool print_error(int lineNum, char *ErrorFormat, ...);


/**
* This method opens a file
* @param fileName the name of the file followed by .as
* @param suffix the new suffix to replace as (for example openFile("test.as", "am") = "test.am")
* @return the opened file
*/
FILE *openFile(char *fileName, char *suffix);

#endif
