#include "funcs.h"
#include "head.h"
#define table32 "!@#$%^&*<>abcdefghigklmnopqrstuv"

/**
* creates the ob file and print to it the command table and the data table
* @param commandTable the command table
* @param dataTable the data table
* @param fileName the name of the source file (eg. {file name}.as)
*/
void translate(word_list commandTable, word_list dataTable, char *fileName);


/**
* prints the table to obFile the correct way(in special 32-base)
* @param obFile the ob file
* @param table the table to be printed
*/
void printTable(FILE *obFile, word_list table);


/**
* translate the word to 32-base
* @param word a general word to translate
* @return a string consist of the 32-base representaion of word
*/
char * translateTo32(Word word);


/**
* translate n to 32-base
* @param n a number to translate to 32-base
* @return a string consist of the 32-base representaion of n
*/
char *translateNumTo32(int n);


void createextern_or_entry(table_head *symbolTable, char *fileName);
