#include "head.h"
#include "utils.h"
#include "symbol_table.h"

/*-----------------------------------------------------------------------------------*/
/* This function gets a word and check if the word is part of the "special keywords" of
the assembley language.
return true if it's a reserved word otherwise false.
*/
bool isReservedWord(char *word);

void move_to_next_token(char **line);


/*-----------------------------------------------------------------------------------*/
/* This function gets a word and a character 'a' and checks if the first letter in the word
equal to 'a'.
The function return true if the first letter in word equal to 'a'
otherwise false.
*/
bool first_str_character(char *word, char a);


/*-----------------------------------------------------------------------------------*/
/* This function gets a word and a character 'a' and checks if the last character in the word
equal to 'a'.
The function return true if the first character in word equal to 'a'
otherwise false.
*/
bool last_char_in_word(char *word, char a);


/*-----------------------------------------------------------------------------------*/
/* This function gets a line and return true if the first character in the line is
equal to ';'.
the function using "first_str_character" to check the first letter in the line.
The function return true if the first letter in word equal to ';'
otherwise false.
*/
bool is_comment(char *line);


/*-----------------------------------------------------------------------------------*/
/* This function gets a word and checks if the word has a valid lable syntax.
if the word has only alphanumeric characters and the first character in the
word is a letter the function return true.
otherwise false.
*/
bool valid_lable_syntax(char *word);


/*-----------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
/* This function gets a word and checks if the word is a whole number.
returns true if its a whole number
otherwise false.
*/
bool is_int(char *word);


/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
/* This function gets a "number" and checks if the number is a whole number.
returns true if the number is greater or equal to zero
otherwise false.
*/
bool is_positive(char *num);


/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* This function gets a word and checks if the word its a register name.
returns true if its a register name
otherwise false.
*/
bool is_reg(char *word);


/*--------------------------------------------------------------------------------*/


/* This function gets a word and checks if the word is a immediate operand.
if its a immediate operand the function returns true
otherwise false.
*/
bool is_immediate(char *data);


/*--------------------------------------------------------------------------------*/



/* This function gets a word and checks if the word is a struct type operand.
if its a immediate operand the function returns true
otherwise false.
*/
bool is_struct(char *word, table_head *ptr);

bool is_valid_label(char *word);


/*--------------------------------------------------------------------------------*/
