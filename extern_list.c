#include "extern_list.h"
#include "translate.h"

/** The Method insert the data into the extern symbol table */
void insert_extern(extern_list *lst, char *word, extern_or_entry type) 
{
    external_node *en = (external_node *) malloc(sizeof(external_node));/* temporary node */
    check_if_memory_allocated(en)
    en->Name = (char *) malloc(sizeof(char) * strlen(word));
    strcpy(en->Name, word);
    en->type = type;

    en->next = lst->head;
    lst->head = en;
}

/* The Method checks if word exist inside the extern table. */
bool is_external(extern_list *lst, char *word) 
{
    external_node *ptr = lst->head;
    while(ptr) 
    {
        if (strcmp(ptr->Name, word) == 0) 
            return ptr->type;
        ptr = ptr->next;
    }
    return -1;
}

/*  The Method prints the extern list into file.ext */
void print_extern_table(FILE *ext, char *name, int adress) 
{
    fprintf(ext, "%s ", name);
    fprintf(ext, "%s\n", translateNumTo32(adress + 100));
}


void print_extern_list(extern_list *lst) 
{
    external_node *ptr = lst->head;
    while(ptr) {
        /*printf("%s ", ptr->Name);
        printf("%d\n", ptr->type);*/
        ptr = ptr->next;
    }
}
