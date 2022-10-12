#include "funcs.h"

int search_command(char *command) 
{
    int i;
    for (i=0; i<16; i++) 
    {
        if (strcmp(global_table[i].cmd, command) == 0)
            return i;
    }
    return -1;
}


command_opcode *analyze_command(char *line, int lineNum) 
{ 
    char *command, *src="0", *dest="0", *token = " \t\n", *seperator = " \t\n,";
    int i;
    command_table cmd;
    command_opcode *curr_command = (command_opcode *) malloc(sizeof(command_opcode));
    int L = 1;      /* the number of words the command is translated to */

    check_if_memory_allocated(curr_command)
    
    command = strtok(line, token);     /* the command is the first word of line    */
    i = search_command(command); /* searching the global_table with all commands for the first word  */
    if (i == -1) 
    {
        print_error(lineNum, "Error: first word %s is not a command", command);
        return NULL;
    }
    cmd = global_table[i];

    /* the default values of the word */
    curr_command->ARE = 0;
    curr_command->op_code = cmd.op_code;
    curr_command->src = 0;
    curr_command->dest = 0;
    
    /* inputting src and dest */
    if (cmd.srcSyntx != NONE && cmd.destSyntx != NONE) 
    {
        src = strtok(NULL, seperator);
        dest = strtok(NULL, seperator);
    }
    else if (cmd.destSyntx != NONE) 
    {
        dest = strtok(NULL, token);
        if (strtok(NULL, seperator)) 
        {
            print_error(lineNum, "Error: input not compatible(the command %s expected 1 argument and 						got 2)", command);
            return NULL;
        }
    }
    else if (strtok(NULL, token)) 
    {
        print_error(lineNum, "Error: input not compatible (the command %s expected 0 arguments and got 						more than 0)", command);
        return NULL;
    }
    if (!src || !dest) 
    {        /* checks if any of the strtok failed */
        print_error(lineNum, "Error: input not compatible (wrong number of arguments)");
        return NULL;
    }

    if (cmd.destSyntx != NONE) 
    {        /* if there should be a first operand */
        L++;        /* that means we need to translate at least two words */

        if (is_immediate(dest) && cmd.destSyntx != NOT_CONSTANT)
            curr_command->dest = 0;
        else if (is_label(dest)) 
        {
            curr_command->dest = 1;
        }
        else if (is_struct_label(dest)) 
        {
            curr_command->dest = 2;
            L++;        /* need to add num of field word */
        }
        else if (is_register(dest))
            curr_command->dest = 3;
        else 
        {
            print_error(lineNum, "Error: input not compatible (dest argument isn't legal)");
            return NULL;            /* not sure if will work */
        }
        
        if (cmd.srcSyntx != NONE) 
        {         /* if src operand is needed */
            L++;
            if (is_immediate(src) && cmd.srcSyntx != LABEL)
                curr_command->src = 0;
            else if (is_label(src))
                curr_command->src = 1;
            else if (is_struct_label(src)) 
            {
                curr_command->src = 2;
                L++;
            }
            else if (is_register(src) && cmd.srcSyntx != LABEL)  
            {
                curr_command->src = 3;
                if (curr_command->dest == 3)
                    L--;
            }
            else 
            {
                print_error(lineNum, "Error: input isn't compatible with command (src argument isn't 							legal)");
                return NULL;     /* again not sure */
            }
        }
    }
    IC += L;
    return curr_command;
}


immediate_opcode analysNumber(char *num) 
{
    immediate_opcode res;
    char *end;
    res.NUM = strtol(num, &end, BASE);
    res.ARE = 0;
    return res;
}



register_opcode analyze_register(char *dest, char *src) 
{
register_opcode rg;

    rg.ARE = 0;
    rg.destReg = 0;
    rg.srcReg = 0;
    if (dest)
        rg.destReg = (int) (dest[1]-'0');
    if (src)
        rg.srcReg = (int) (src[1] - '0');
    return rg;
}
