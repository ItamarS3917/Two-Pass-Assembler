#include "head.h"
#include "symbol_table.h"
#include "first_line_check.h"

/* initializing a Pointer to the head of symbol table */
void create_table_head(table_head *table_head)
{
	table_head -> head = NULL;
}

/* Initialize an empty node in the symbol table */
void create_label(symbol_table *table_ptr)
{
	table_ptr->name = (char *) malloc(sizeof(char) * LABLE_LENGTH);

	table_ptr -> address = 0;
	table_ptr -> type = none;
	table_ptr -> next = NULL;
	table_ptr -> _entry = false;
	table_ptr -> _extern = false;
}

/* The function checks the data and, if it is correct, 
   sends it to the functions that will be inserted into the nodes in the symbol
   table */
void add_only_label_symbol(table_head *head, char *name,unsigned int *IC, unsigned int *DC, symbol_type type, int lineNum)
{
	symbol_table *new_node = (symbol_table *)malloc(sizeof(symbol_table));
	check_if_memory_allocated(new_node)
	create_label(new_node);	/* creating empty symbol table node*/
	
	if (is_empty_table(head->head)) 
	{
		add_first_label(head, name,IC,DC, type, new_node);
		if (check_if_exist(head->head, name) == false)
			printf("Error:in line %d the label is not inserted to the  symbol table\n", lineNum);
	}
	else if (!check_if_exist(head->head, name))	/* the label dosen't exist in the table*/
	{
		add_to_symbol_table(head, name,IC,DC, type, new_node);
		if (check_if_exist(head->head, name) == false)		/* TODO: doesn't understand */
			printf("Error:in line %d the label is not inserted to the  symbol table\n", lineNum);
	}		
	else 
	{
		printf("Error:in line %d the label is not inserted to the  symbol table\n", lineNum);
		free(new_node);
	}

}

/* The function inserts data into the first node in the symbol table */
void add_first_label(table_head *first_node, char *label_name,unsigned int *IC, unsigned int *DC, symbol_type label_type, symbol_table *new_node)
{
	
	strcpy(new_node -> name, label_name);
	new_node -> next = NULL;
	first_node -> head = new_node;
	new_node -> address = 0;
	new_node -> type = label_type;

	if (label_type == is_code)
		new_node -> address = *IC;
	else if(label_type == is_data)
		new_node -> address = *DC;	
}
/** @todo remove *IC *DC */
/* The function inserts data into the second node and beyond in the symbol table*/
void add_to_symbol_table(table_head *first_node, char *label_name,unsigned int *IC, unsigned int *DC, symbol_type label_type, symbol_table *node)
{
	symbol_table *ptr = first_node -> head;	/* Pointer to traverse the table */

	while (ptr -> next != NULL && ptr != NULL)
		ptr = ptr -> next;	/* getting to the last place in the table */

	strcpy(node -> name, label_name);
	node -> address = 0;
	node -> next = NULL;
	ptr -> next = node;	/* connects the new node to the last index in the table */
	node -> type = label_type;
	if (label_type == is_code)
		node -> address = *IC;
	else if(label_type == is_data)
		node -> address = *DC;	

}

/** updates the entry filed of a node */
bool update_entry_symbol(symbol_table *node, int line_num)
{
	symbol_table *ptr = node;
	if (ptr != NULL)
	{
		if (node -> _extern == true)
		{
			print_error(line_num, "Error: label can't be entry and extern");
			return false;
		}	
		else
		{
			ptr -> _entry = true; 
			return true;
		}		
	}
	else
		print_error(line_num, "Error: label does not exist");
	return false;	
}

bool check_if_exist(symbol_table *head, char *name)
{
	while (head != NULL)
	{
		if (strcmp(head -> name, name) == 0)
			return true;
		head = head -> next;	
	}
	return false;	
}


void free_symbol_table(table_head *ptr)
{
	label_ptr prev_node, curr_node = ptr->head;
	while (curr_node != NULL)
	{
		prev_node = curr_node;
		curr_node = curr_node -> next;
		free(prev_node -> name);
		free(prev_node);
	}
}

bool is_empty_table(label_ptr head)
{
	return (head) ? false: true;
}

/* gets a pointer to table head and a name.
   returns a pointer to name if exist otherwise NULL */
symbol_table *get_label(char *label_name, table_head *ptr)
{
	symbol_table *symbol_to_match = ptr->head;

	while (symbol_to_match)	/* The symbol table not empty*/
	{
		if (strcmp(symbol_to_match ->name, label_name) == 0)
			return symbol_to_match;
		symbol_to_match = symbol_to_match -> next;		
		
	}
	
	return NULL;	/* lable not found inside the symbol table*/
}


void printSymbolList(table_head *lst) {
    label_ptr ptr = lst->head;
    while(ptr) {
        printf("%s ", ptr->name);
        printf("%d ", ptr->address);
		printf("%d\n", ptr->type);
        ptr = ptr->next;
    }
}
