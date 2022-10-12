#include "head.h"
#ifndef extern_list_INCLUDED
#define extern_list_INCLUDED


typedef enum extern_or_entry {
    ext, ent
} extern_or_entry;   /* type of external_node, wethere the node is extern or entry */


/** Extern nodes symbol table */
typedef struct external_node {
    char *Name;
    extern_or_entry type;
    struct external_node *next;
}  external_node;


/** Head of extern symbol table */
typedef struct extern_list {
    external_node *head;
} extern_list;


/**
* The Method insert the data into the extern symbol table
* @param lst Pointer to the head of extern table
* @param word The label name.
* @param type entry or extern
*/
void insert_extern(extern_list *lst, char *word, extern_or_entry type);


/**
* The Method checks if word exist inside the extern table.
* @param lst Pointer to the head of extern table
* @param word The label name.
* @return true if word is found otherwise return -1.
*/
bool is_external(extern_list *lst, char *word);


/**
* The Method prints the extern list into file.ext
* @param ext The file 
* @param name The label name.
* @param adress the symbol address
*/
void print_extern_table(FILE *ext, char *name, int adress);


void print_extern_list(extern_list *lst);

#endif
