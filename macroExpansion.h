#include "head.h"

#ifndef macroExpansion_INCLUDED

#define macroExpansion_INCLUDED 0

#define lineCharCycle 10	/* delete */

typedef struct MACRO {
    char *name;
    int startLine;
	int endLine;
} macro;


typedef struct MACRO_NODE macroNode;
struct MACRO_NODE {
	macro m;
	struct MACRO_NODE *next;		/* fix to look nicer */
};


struct macroList {
	macroNode *head;
};


typedef struct macroList macroList;

/** 
* The method gets a file and checks for macro statements and every time the method found a macro name 
* it copy the content of the macro to the file.
* @param fileName The file name
* @param src Source file
* @return Pointer to the Expanded file.
 */
FILE *macroExpand(char *fileName, FILE *src);

/** 
* This method checks if the macro have a legal name
* @param name The macro name
* @return true if the name is legal else false
 */
bool legalMacro(char *);


bool getLineAsmb(FILE *, char **);

void insertMacro(macroList *, macro *);
macro * search(macroList *, char *);
void freeMacroList(macroList *lst);

bool reservedWord(char *name);

bool in(char *name, char *lst[], int length);

#endif
