#include "head.h"
#include "global_var.h"
#include "symbol_table.h"
#include "utils.h"
#include <ctype.h>


/**
* The Method checks if word has a valid label syntax
* @param word Check this word
* @return true if word has a valid label syntax otherwise false.
*/
bool valid_lable_syntax(char *word);


/**
* This function gets a word and checks if the word is a valid command.
* @param word Check this word
* @return true if word is a command otherwise false.
*/
bool is_cmd(char *word);


/**
* This function gets a word and checks if its a guidance instruction.
* @param word Check this word
* @return 
* 0 for .data
* 1 for .string
* 2 for .struct
* 3 for .entry
* 4 for .extern
* 5 for wrong value
*/
int is_data_str_struct_entry(char *word);


/**
* This method checks if word is a assembly reserved word.
* @param operand Check this word
* @return true if word is a reserved word otherwise false.
*/
bool assembler_key_words(char *word);


/**
* This method gets a word and checks if word is a valid register name.
* @param word Check this word
* @return true if word is valid register name (r1,r2,...,r7) otherwise false.
*/
bool is_register(char *word);


/**
* This method gets a word and checks if word is a immediate operand.
* @param word Check this word
* @return true if word is immediate operand otherwise false.
*/
bool is_immediate(char *word);


/**
* This method gets a word and checks if word has a valid label syntax.
* @param word Check this word
* @return true if word valid label syntax otherwise false.
*/
bool is_label(char *word);


/**
* This method gets a word and checks if the word has a valid struct parameters.
* @param word Check this word
* @return true if word is a valid struct otherwise false.
*/
bool is_struct_label(char *word);






