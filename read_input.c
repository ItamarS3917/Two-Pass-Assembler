#include "read_input.h"
/* This program takes an unbounded number of assembly source files and creates 32-base translation of the files */

int main(int argc, char *argv[]) {
    int i;
    for(i = 1; i<argc; i++) {
        assembler(argv[i]);     /* for each file passes we call the assembler that creates all the translated files */
    }
    return 0;
}

/*
    assembler calls 4 functions that are responsible for each step of creating the translated files.
    it calls preAssembler (macro expansion), firstPass (first translation and detection of labels), second pass(filling missing data from firstPass),
    translate(tranlating command_table and data_table to 32-base and printing it on screen).
*/
void assembler(char *fileName)
 {
    /** initilizing files, data tables and symbol/extern tables */
    FILE *expanded = preAssembler(fileName), *ext, *ent;        /* returns the file with name fileName after macro expansion */

    word_list command_table = {NULL, NULL};
    word_list data_table = {NULL, NULL};

    table_head head;

    extern_list ext_lst = {NULL};

    bool passWorked;

    create_table_head(&head);

    ext = openFile(fileName, "ext");
    ent = openFile(fileName, "ent");
    
  
	printf("----------------------Srarting first pass...--------------------------\n\n\n");

    passWorked = first_pass(expanded, &command_table, &data_table, &head, &ext_lst);

    if (!passWorked)
    {
    	printf("----------------------Error found in first pass. please try again--------------------------\n");
        return;
	}

	printf("\n----------------------Srarting second pass...--------------------------\n\n\n");
	
    passWorked = second_pass(expanded, &command_table, &head, &ext_lst, ent, ext);

    if (!passWorked)
    {
    	printf("----------------------Error found in second pass. please try again--------------------------\n");
        return;
    }
    
  
	printf("----------------------Srarting to process output files...--------------------------\n\n");
	
    translate(command_table, data_table, fileName); 
    
    printf("Process completed.\nGood Bye..\n\n");

    freeList(command_table);
    freeList(data_table);
    free_symbol_table(&head);
}


FILE *preAssembler(char *fileName) {
    FILE *src = fopen(fileName, "r");
    FILE *srcExpanded;
    if (!src) {
      return NULL;
    }
    srcExpanded = macroExpand(fileName, src);
    fclose(src);
    return srcExpanded;
}

FILE *openFile(char *fileName, char *suffix) {
    char *newFileName = malloc(sizeof(char) * strlen(fileName) + strlen(suffix));
    FILE *file;
    strncpy(newFileName, fileName, strlen(fileName) - 2);      /* copy the fileName without as ending */
    strcat(newFileName, suffix);     /* adds suffix */    /* adds suffix */
    file = fopen(newFileName, "w+");
    if (!file) {
        printf("Error: couldn't open a new file called: %s\n", newFileName);
        exit(0);
    }
    return file;
}
