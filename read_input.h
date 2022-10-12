#include <string.h>
#include <ctype.h>
#include "head.h"
#include "funcs.h"
#include "second_pass.h"
#include "first_pass.h"
#include "symbol_table.h"
#include "translate.h"


/** 
 * wrapper function to all translation,
 * takes a fileName (doesn't assume existance of file) 
 * compile the assembly file and translate the file 
 * into 32 base.
 * @param fileName The name of the file to operate.
 */
void assembler(char *fileName);     

FILE *macroExpand(char *fileName, FILE *src);

/**
 *  gets a source file before the pre assembler stage
 * copy the macro into a linked list and paste it back
 * when it encouter it inside the file
 * @param fileName The file name
 * @return FILE* Pointer to the expanded file
 */
FILE *preAssembler(char *fileName);

