#include "first_line_check.h"

/* The function checks if the syntax of the symbol is correct */
bool valid_lable_syntax(char *word) 
{
    int len = strlen(word);
    int alpha = (int)word[0];
    if ((len > LABLE_LENGTH - 1) || !(isalpha(alpha)))
    {
        return false;
    }
    if (assembler_key_words(word))	/** word is a special key word */
	{
		return false;
	}
    if (!(is_alpha_digit(word))) /* The label has only letters or digits */
        return false;
    return true;
}



/* This function checks if a given word is a command*/
bool is_cmd(char *word)
{
    command_table *ptr = global_table;
	int i;

    for(i=0; i<CMD_NUM; i++) {
        if (strcmp(ptr->cmd, word) == 0)
            return true;
        ptr++;
	}

    return false;
}


/** This function gets a word and checks if its a guidance instruction. */
int is_data_str_struct_entry(char *word)
{
	int i;
	for(i=0; i<5; i++) 
    {
		if (strcmp(inst_types[i], word) == 0)
			return i;
	}
	return 5;	/** for every word that's not an guidence instruction */
}

/** This method checks if word is a assembly reserved word. */
bool assembler_key_words(char *word)
{
	if (is_cmd(word) || is_register(word) ||
		(is_data_str_struct_entry(word) > 0 && is_data_str_struct_entry(word) < 5))
		return true;	
	return false;	
}


bool is_register(char *word)
{
    return word[0] == 'r' && word[1] >= '0' && word[1] <= '7';
}


/* The method checks if word has a label name */
bool is_label(char *word) 
{
    return valid_lable_syntax(word);
}


/* The method checks if word is immediate type */
bool is_immediate(char *word) 
{
    if (word[0] == '#')
        return is_int(word + 1);
    return false;
}

/* The method checks if word is a valid struct */
bool is_struct_label(char *word) 
{
    char *tmp;
    tmp = strtok(word, ".");
    if (valid_lable_syntax(tmp)) 
    {
        tmp = strtok(NULL, " \t\n");
        if ((tmp[0] == '1' || tmp[0] == '2') && tmp[1] == '\0')
            return true;
    }
    return false;
}