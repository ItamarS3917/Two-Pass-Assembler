#include "macroExpansion.h"
#include "global_var.h"

/* 		add to the paramaters macroArr 

        illigal names: assembly's commands, starting numbers, already in macroArr, 
*/
bool legalMacro(char *name) 
{       
    if (!name)
        return false;
    if (reservedWord(name))
        return false;
    if (isdigit(name[0]))
        return false;
    return true;
}

/* checks if name is a reserved word */
bool reservedWord(char *name) 
{
    /*fd*/
    return in(name, two_operands_cmd,5) || in(name, one_operands_cmd,9) || in(name,				  		zero_operands_cmd,2) || in(name, regs_list,8) || in(name, instruction_type,5) ||
    		in(name, macroRelated, 2);
}


/* check if name is a command */
bool is_command(char *name) 
{
    return in(name, two_operands_cmd,5) || in(name, one_operands_cmd,9) ||in(name, zero_operands_cmd,2);
}



/* check if name is in lst */
bool in(char *name, char *lst[], int length) 
{
    for (; length > 0; length--) 
    {
        if (strcmp(name, lst[length-1]) == 0)
            return true;
    }
    return false;
}
