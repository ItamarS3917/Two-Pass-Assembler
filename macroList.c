#include "macroExpansion.h"

void insertMacro(macroList *lst, macro *mac) 
{
    /* 1. allocate node */
    macroNode *new_node = (macroNode *) malloc(sizeof(macroNode));

	check_if_memory_allocated(new_node)
   
    /* 2. put in the data  */
    new_node->m  = *mac;
   
    /* 3. Make next of new node as head */
    new_node->next = lst->head;
   
    /* 4. move the head to point to the new node */
    lst->head  = new_node;
}


macro * search(macroList *lst, char *name) 
{
	macroNode *ptr;
	if (name == NULL)
		return NULL;
	for(ptr = lst->head; ptr != NULL; ptr = ptr->next) 
	{
		if (strcmp(name, ptr->m.name) == 0)
			return &(ptr->m);
	}
	return NULL;
}

void freeMacroList(macroList *lst) 
{
	macroNode *ptr = lst->head;
	macroNode *tmp;
	while (ptr) 
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}
