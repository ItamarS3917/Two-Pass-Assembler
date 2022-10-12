#ifndef UTILS
#define UTILS
#include "head.h"
#include "str_methods.h"
#include <ctype.h>


/*----------------------------------------------------------------------------------------*/
/* This function gets a word and return true if the characters in the word are letters or digits */
bool is_alpha_digit(char *word);


/*----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------*/
/* This function gets a line and return true if the commas in line in the right order
	otherwise return false.
*/	
bool comma_in_line(char *line);


/*----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------*/
/* 
	This function removes the white space from the left side of the word
	and returns to caller without the white space in the left side	
*/	
char *remove_left_space(char *word);


/*----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------*/
/* This function gets a size and allocate memory of size 
   if succsesull the function returns the pointer
   otherwise print error massege and exit.
*/
void *check_if_malloc(long size);


/*----------------------------------------------------------------------------------------*/

bool ignored_line(char *line);

void str_copy(char** destination, char* source);
#endif 
