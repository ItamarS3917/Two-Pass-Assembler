#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "constants.h"
#include "head.h"

typedef enum symbol_type {
	is_data,
	is_extern,
	is_code,
	none
} symbol_type;

typedef struct symbol_table {
	/** label (symbol) name */
	char *name;
	/** The symbol address */
	unsigned int address;
	/** if it's a data/code/extern */
	symbol_type type;
	/** Ponter to the next symbol */
	struct symbol_table *next;
	bool _extern;
	bool _entry;
} symbol_table;

typedef struct symbol_table *label_ptr;

/* Pointer to the head of symbol table */
typedef struct table_head {
	/** Head of the symbol table */
	symbol_table *head;
} table_head;


/**
* initializing a Pointer to the head of symbol table
*  @param table_head Pointer to the head of symbol table
*/
void create_table_head(table_head *table_head);

/**
* initializing empty symbol table node
*  @param table_ptr empty node.
*/
void create_label(symbol_table *table_ptr);

/**
* The function gets label name and checks the data to insert to new node.
* if the function get the correct data the function create's a node by using
* add_first_label (if it's the first node) or add_to_symbol_table functions.
* @param table_head Points to the head of symbol table.
* @param name The symbol name.
* @param DC Data counter if it's a symbol of data type.
* @param IC Instruction counter if it's a symbol of code type.
* @param type The symbol type (extern/data/code)
* @param line_number the line number in the file.
*/
void add_only_label_symbol(table_head *head, char *name, unsigned int *DC,unsigned int *IC,symbol_type type, int line_number);


/**
* The function gets the correct data and adds the values to the head of symbol
* table node.
* @param first_node Points to the head of symbol table.
* @param label_name The symbol name.
* @param DC Data counter if it's a symbol of data type.
* @param IC Instruction counter if it's a symbol of code type.
* @param type The symbol type (extern/data/code)
* @param node The new node in the symbol table
*/
void add_first_label(table_head *first_node, char *label_name, unsigned int *DC,unsigned int *IC, symbol_type type, symbol_table *node);

/**
* The function gets the correct data and adds the values to the symbol 
* table node.
* @param first_node Points to the head of symbol table.
* @param label_name The symbol name.
* @param DC Data counter if it's a symbol of data type.
* @param IC Instruction counter if it's a symbol of code type.
* @param type The symbol type (extern/data/code)
* @param node The new node in the symbol table
*/
void add_to_symbol_table(table_head *first_node, char *label_name,unsigned int *DC,unsigned int *IC, symbol_type type, symbol_table *node);


/**
* This methods gets a pointer to entry symbol node and update the entry
* filed of the node.
* @param node Points to the node
*/
bool update_entry_symbol(symbol_table *node, int line_num);


/**
* The function checks if the name already exist inside the symbol table.
* @param head Pointer to the head of symbol table
* @param name The label name.
* @return true if the label exist otherwise return false.
*/
bool check_if_exist(label_ptr head, char *name);


/**
* The function gets a label name and pointer to the head of symbol table
* @param ptr Pointer to the head of symbol table
* @param label_name The label name.
* @return Pointer to label_name if found otherwise return NULL.
*/
symbol_table *get_label(char *label_name, table_head *ptr);


/**
* The function checks whether the symbol table is empty
* @param head Pointer to the head of symbol table
* @return true if the table is empty otherwise false
*/
bool is_empty_table(label_ptr head);


/**
* The function frees the memory space of the symbol table
* @param ptr Pointer to the head of symbol table 
*/
void free_symbol_table(table_head *ptr);

void printSymbolList(table_head *lst);


#endif
