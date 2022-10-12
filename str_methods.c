#include "str_methods.h"

/* This function gets a word and checks if the word is part of the "special keyword" of
the assemmbley language.
*/
bool isReservedWord(char *word)
{
    command_table *ptr = global_table;

    while(!ptr)
    {
        if (strcmp(ptr->cmd, word) == 0)
            return true;
        ptr++;
    }

    return false;
}

void move_to_next_token(char **line) {
	while (isspace(**line)) {
		(*line)++;
	}
	while (!isspace(**line)) {
		(*line)++;
	}
	while (isspace(**line)) {
		(*line)++;
	}
}




/* This function gets a word and a character 'a' and returns true if the last character
in the word equal to 'a' */
bool first_str_character(char *word, char a)
{
    char c = word[0];
    if (c == a)
        return true;

    return false;
}




/* This function gets a word and a character 'a' and returns true if the last character
in the word equal to 'a' */
bool last_char_in_word(char *word, char a)
{
    int len = strlen(word);
    char c = word[len -1];

    if (c == a)
        return true;

    return false;
}


/* This function checks if the line starts with ";" return true if its a comment */
bool is_comment(char *word)
{
    if (first_str_character(word, ';'))
        return true;

    return false;
}


/* This function checks if the word have a valid label syntax*/
bool is_valid_label(char *word)
{
	int len = strlen(word);
	
	
	if ((len > LABLE_LENGTH - 1) || (!isalpha(word[0])))
		return false;
		
	if (is_alpha_digit(word))	/* only letters or numbers */
		return true;
	
	else
		return false;			
}


/* 
	This function returns true if word is a whole number 
*/	
bool is_int(char *word)
{
    int i = 0;

    if (word[0] == '-' || word[0] == '+')
        i++;
    while (i < strlen(word) - 1)
    {
        if (!isdigit(word[i]))
            return false; /* The string is not a legal number */

    	i++;
    }

    return true; /* The string is a valid number */
}

/*
	Gets a "number" and checks if the number is positive
*/
bool is_positive(char *num)
{
	if (atoi(num) >= 0)
		return true;
	return false;	
}


/*
	This function checks if its a valid register name 
*/	
bool is_reg(char *word)
{
	return word[0] == 'r' && word[1] <= '7' && word[1] >= '0';
}


/*
	This function checks if data is immediate operand 
*/	
bool is_immediate(char *data)
{
	char *tmp = data;
	
	if (tmp != NULL)
	{
		if (tmp[0] == '#')
		{
			tmp += 1;
			if (is_int(tmp))	/* data is immediate operand */
				return true;
		}
	}
	
	return false;	
}

/*
	This function checks if data is struct type operand 
*/	

bool is_struct(char *struct_operand, table_head *table_head)
{
	if (struct_operand != NULL)
	{
		char *before_dot, *after_dot;
		char *struct_delim = ".";
		before_dot = strtok(struct_operand, struct_delim);
		after_dot = before_dot + strlen(before_dot) + 1;
		if ((get_label(before_dot, table_head)) && (is_int(after_dot))
			&& (is_positive(after_dot)))
			return true;
	}	
	return false;
}

