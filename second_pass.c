#include "second_pass.h"

bool s_pass_err = false;

bool second_pass(FILE *expanded, word_list *command_table, table_head *label_table, extern_list *ext_lst, FILE *ent, FILE *ext)
{
    char _line[LINE_LENGTH];
    int lineNum=0;
    int address=0;

	word_node *comm = command_table->head;
	rewind(expanded);
    
    while(fgets(_line, LINE_LENGTH, expanded)) /* Read lines until end of file */
    {   
        ++lineNum;
        if (ignored_line(_line) == false) {
            process_line_s_pass(_line, label_table, lineNum, command_table,ext_lst, ent, ext, &comm, &address);
		}
    }
    return print_error(-1, "");
}

/* This function analyzes and extracts information needed for the second pass from a given line */
void process_line_s_pass(char * line, table_head *label_table, int lineNum, word_list *command_table, extern_list *ext_lst, FILE *ent, FILE *ext, word_node **comm, int *address)
{
    int type_instruction;
    symbol_table *symbol_ptr = label_table -> head;
    char *token;
   
    line = remove_left_space(line); /*Removing spaces and tabs until the first word*/
    if(line == NULL || *line == '\0' || *line == '\n') /*If we got an empty line, we will skip to the next line*/ 
        return; 
    str_copy(&token, line);

    if(last_char_in_word(token, ':'))
    { 
        move_to_next_token(&line);  /*if label found skip the label to next token */
        str_copy(&token, line);
    }
    type_instruction = is_data_str_struct_entry(token);
        if (type_instruction == _ENTRY)
        {
			move_to_next_token(&line);
			str_copy(&token, line);
            symbol_ptr = get_label(token, label_table);
            fprintf(ent, "%s ", symbol_ptr->name);
			fprintf(ent, "%s\n", translateNumTo32(symbol_ptr->address));
		}
    else if (is_command(token))
    {
        *address = fillBlanks(line, *command_table, comm, label_table, lineNum, *address, ext_lst, ext);
    }
}


/** This method fills the empty words that generated in the first pass */
int fillBlanks(char *line, word_list command_table, word_node **firstWord, table_head *label_table, int lineNum, int address, extern_list *extLst, FILE *extFile) 
{
    command_opcode comm = (*firstWord)->word.word.cmd;    /* assumes firstWord is a cmd command */
    union generate_command_opcode genWord;
    char *dest, *src = NULL;
    symbol_table *ptr;
    extern_or_entry tmp;
    *firstWord = (*firstWord)->next;
	address++;
    strtok(line, " \t\n");  /* skip the command */
 
 
    if (global_table[comm.op_code].destSyntx != NONE)
    {
        dest = strtok(NULL, " \t\n,");
        if (global_table[comm.op_code].srcSyntx != NONE) 
        {
            src = dest;
            dest = strtok(NULL, " \t\n,");
            /*
            analyse src
            */
		        switch(comm.src) 
		        {
		            case 0:
		                genWord.adnum = analysNumber(src + 1);
		                (*firstWord)->word.word = genWord;
		                (*firstWord)->word.type = adress_num;
		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;
		            case 1:
		                ptr = get_label(src, label_table);
		                tmp = is_external(&extLst, src);
		                if (!ptr)
		                {
		                    if (tmp == ext)
		                    {
		                        genWord.adnum.NUM = 0;
		                        genWord.adnum.ARE = 1;
		                        print_extern_table(extFile, src, address);
		                    }
		                    else
		                    {
		                        print_error(lineNum, "Error: non-existing label put as input");
		                    }
		                }
		                else 
		                {
		                    genWord.adnum.NUM = ptr->address;
		                    genWord.adnum.ARE = 2;
		                }
		                

		                (*firstWord)->word.word = genWord;
		                if (tmp != ext)
		                    (*firstWord)->word.type = adress_num;
		                else
		                    (*firstWord)->word.type = ext;

		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;
		            case 2:
		                src = strtok(src, ".");
		                ptr = get_label(src, label_table);
		                tmp = is_external(&extLst, src);
						
		                if (!ptr) 
		                {
		                    if (tmp == ext) 
		                    {
		                        genWord.adnum.NUM = 0;
		                        genWord.adnum.ARE = 1;
		                        print_extern_table(extFile, src, address);
		                    }
		                    else 
		                    {
		                        print_error(lineNum, "Error: non-existing label put as input");
		                    }
		                }
		                else 
		                {
		                    genWord.adnum.NUM = ptr->address;
		                    genWord.adnum.ARE = 2;
		                }
		                (*firstWord)->word.word = genWord;
		                if (tmp != ext)
		                    (*firstWord)->word.type = adress_num;
		                else
		                    (*firstWord)->word.type = ext;

		                (*firstWord) = (*firstWord)->next;
		                address++;
		                src = strtok(NULL, " \t\n.");
		                genWord.adnum = analysNumber(src);
		                (*firstWord)->word.word = genWord;
		                (*firstWord)->word.type = adress_num;
		                (*firstWord) = (*firstWord)->next;
		                address++;
						
		                break;
		            case 3:
						if (comm.dest == 3)
							genWord.reg = analyze_register(dest, src);
						else
							genWord.reg = analyze_register(NULL, src);
		                (*firstWord)->word.word = genWord;
						(*firstWord)->word.type = reg;
		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;    
		        }	/* end switch */
	        }
        /*
        analyse dest
        */
		    switch(comm.dest) 
		    {
		    
		            case 0:
		                genWord.adnum = analysNumber(dest + 1);
		                (*firstWord)->word.word = genWord;
		                (*firstWord)->word.type = adress_num;
		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;
		            case 1:
		                ptr = get_label(dest, label_table);
		                tmp = is_external(&extLst, dest);
		                if (!ptr) 
		                {
		                    if (tmp == ext) 
		                    {
		                        genWord.adnum.NUM = 0;
		                        genWord.adnum.ARE = 1;
		                        print_extern_table(extFile, dest, address);
		                    }
		                    else 
		                    {
		                        print_error(lineNum, "Error: non-existing label put as input");
		                    }
		                }
		                else 
		                {
		                    genWord.adnum.NUM = ptr->address;
		                    genWord.adnum.ARE = 2;
		                }
		                (*firstWord)->word.word = genWord;
		                if (tmp != ext)
		                    (*firstWord)->word.type = adress_num;
		                else
		                    (*firstWord)->word.type = ext;

		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;
		            case 2:
		                dest = strtok(dest, ".");

		                ptr = get_label(dest, label_table);
		                tmp = is_external(&extLst, dest);
		                if (!ptr) 
		                {
		                    if (tmp == ext) 
		                    {
		                        genWord.adnum.NUM = 0;
		                        genWord.adnum.ARE = 1;
		                        print_extern_table(extFile, dest, address);
		                    }
		                    else 
		                    {
		                        print_error(lineNum, "Error: non-existing label put as input");
		                    }
		                }
		                else 
		                {
		                    genWord.adnum.NUM = ptr->address;
		                    genWord.adnum.ARE = 2;
		                }
		                (*firstWord)->word.word = genWord;
		                if (tmp != ext)
		                    (*firstWord)->word.type = adress_num;
		                else
		                    (*firstWord)->word.type = ext;

		                (*firstWord) = (*firstWord)->next;
		                address++;
		                dest = strtok(NULL, ". \t\n");
		                genWord.adnum = analysNumber(dest);
		                (*firstWord)->word.word = genWord;
		                (*firstWord)->word.type = adress_num;
		                (*firstWord) = (*firstWord)->next;
		                address++;
		                break;
		            case 3:
		                if (comm.src != 3) {
		                    genWord.reg = analyze_register(dest, NULL);
		                    (*firstWord)->word.word = genWord;
		                    (*firstWord)->word.type = reg;
		                    (*firstWord) = (*firstWord)->next;
		                    address++;
		                } 
		                break;    
		    } /* end switch*/
	    }
    return address;
}
