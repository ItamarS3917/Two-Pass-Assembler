#include "macroExpansion.h"


/** The method gets a file and checks for macro statements and every time the method found a macro name 
*  it copy the content of the macro to the file  
 */
FILE *macroExpand(char *fileName, FILE *src) 
{
    FILE *expanded;                 /* the expanded file */
    macroList macroTable = {NULL};  /* the macro collection */
    bool inMacro = false;           /* a flag to check if we're in a macro defenition */
    char *content = (char *) malloc(sizeof(char) * LINE_LENGTH), *line = (char *) malloc(sizeof(char) * LINE_LENGTH);
    char *word, *token=" \t\n";
    macro * tempMac;
    int i, temp, lineNum=1;          /* for indexing */

    check_if_memory_allocated(content); check_if_memory_allocated(line);

    expanded = openFile(fileName, "am");

    if (!expanded)      /* probably can't fail so it's fine */
        return NULL;        /* might wanna do something different here */
    
    while(fgets(line, LINE_LENGTH ,src)) 
    {
        strcpy(content, line);
        word = strtok(content, token);
        if (!word) 
        {                        /* an empty line (only blank characters) */
            if (!inMacro)
                fprintf(expanded, "%s", content);
        }
        else if (strcmp(word, "macro") == 0) 
        {
            if (inMacro)
                print_error(lineNum, "Error: macro %s defined inside macro %s",                      strtok(NULL, " "),        macroTable.head ->m.name);        /* this will cause unexpected behaviour when Error (need to check) */
            else 
            {
                word = strtok(NULL, token);
                if (legalMacro(word) && strtok(NULL, " ") == NULL && !search(&macroTable, word)) 
                {
                    tempMac = (macro *) malloc(sizeof(macro)); /**/
                    check_if_memory_allocated(tempMac)
                    tempMac->name = (char *) malloc(sizeof(char) * strlen(word));
                    check_if_memory_allocated(tempMac->name)
                    strcpy(tempMac->name, word);
                    tempMac->startLine = ftell(src);
                    tempMac->endLine = -1;
                    insertMacro(&macroTable, tempMac);
                    inMacro = true;
                }
                else
                    print_error(lineNum, "Error: macro %s is poorly defined", word);     /* this will cause unexpected behaviour when Error (need to check) */
            }
                
        }
        else if (strcmp(word, "endmacro") == 0) 
        {
            if (!inMacro) 
                print_error(lineNum, "Error: endmacro statement outsided of a macro");
            else if (strtok(NULL, token))
                print_error(lineNum, "Error: word after endmacro");
            else 
            {
                macroTable.head->m.endLine = ftell(src) - strlen(line) + 1;
                inMacro = false;
            }
        }
        else if ((tempMac = search(&macroTable, word))) 
        {
            if (inMacro)
                print_error(lineNum, "Error: macro %s is called inside macro %s", tempMac->name, macroTable.head->m.name);
            else 
            {
                temp = ftell(src);
                fseek(src, tempMac->startLine, SEEK_SET);
                for(i=tempMac->startLine+1; i<tempMac->endLine; i++) {     /* i is +1 because ftell is where \n is in line so we need to get one after */
                    char h = fgetc(src);
                    fprintf(expanded, "%c", h);
                }
                fseek(src, temp, SEEK_SET);
            }
        }
        else 
        {
            if (!inMacro)
                fprintf(expanded, "%s", line);
        }
        lineNum++;
    }
    
    free(content);
    free(line);
    freeMacroList(&macroTable);

    rewind(expanded);

    return expanded;
   } 
