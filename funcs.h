#ifndef FUNCS_H
#define FUNCS_H

#include "head.h"
#include "global_var.h"
#include "utils.h"
#include "symbol_table.h"
#include "first_line_check.h"
#include "str_methods.h"
#include "extern_list.h"


/** Opcode encode */
typedef struct command_opcode {
    unsigned int ARE: 2;                
    unsigned int dest: 2;               
    unsigned int src: 2;
    unsigned int op_code: 4;
} command_opcode;

/** immediate operand encode  */
typedef struct immediate_opcode {
    unsigned int ARE: 2;
    unsigned int NUM: 8;
} immediate_opcode;

/** registers encode */
typedef struct register_opcode {
    unsigned int ARE: 2;
    unsigned int destReg: 4;
    unsigned int srcReg: 4;
} register_opcode;

/** data encode */
typedef struct data_word {
    unsigned int DATA: 10;
}data_word;

typedef enum Type {
    reg, adress_num, cmd, data, empty
}type;

/** union to generate all types of words in the assembly language */
union generate_command_opcode {
    register_opcode reg;
    immediate_opcode adnum;
    command_opcode cmd;
    data_word data;
};

typedef struct Word {
    union generate_command_opcode word;
    enum Type type; 
} Word;

typedef struct word_node word_node;

struct word_node {
    Word word;
    word_node *next;
    word_node *prev;
};

typedef struct word_list {
    word_node *head;
    word_node *tail;
} word_list;

/** converts every 5 bits in binary base into a single bit in 32 base */
typedef struct wordForTranslation {
    unsigned int firstHalf: 5;
    unsigned int secondHalf: 5;
} wordForTranslation;


/**
* The Method gets a command name and search for the command in the command table
* @param command  
* @return if command found return's the command number else return's -1.
*/
int search_command(char *command);


/**
* The Method gets a line and a the line number in the source file and converts the line
* into a assembly opcpde lines depend on the command parameters.
* @param line The command line  
* @param lineNum The line number from the source file.
* @return Pointer to the encoded opcode line
*/
command_opcode *analyze_command(char *line, int lineNum);


/**
* This method gets an immediate number and encode the line
* @param num The number to encode.
* @return Pointer to the encoded immediate line
*/
immediate_opcode analysNumber(char *num);


/**
* This method gets an source and destination registers and encode the line
* @param dest The destination register
* @param src The source register.
* @return Pointer to the encoded register's line
*/
register_opcode analyze_register(char *dest, char *src);


/**
* This method insert to a word list a given word
* @param lst the list of words
* @param word the word to be inserted
*/
void insert(word_list *lst, Word word);

/**
* This method insert a given amount of empty elements to a word list
* @param lst the list of words
* @param n the number of empty words to be inserted to lst
*/
void insert_empty_line(word_list *lst, int n);

/**
* This method free the memory kept by the word list
* @param lst the word list to be freed
*/
void freeList(word_list lst);
void printList(word_list lst);

bool is_command(char *name); 


bool is_external(extern_list *lst, char *word);

#endif

