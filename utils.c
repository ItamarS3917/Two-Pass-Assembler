#include "utils.h"



/* This function gets a word and return true if the characters in the word are letters or digits */
bool is_alpha_digit(char *word)
{
    int i, length = strlen(word);

    for (i = 0; i < length; i++)
    {
	    if ((!isalpha(word[i])) && (!isdigit(word[i])))
            return false;
    }

    return true;
}

/*
	This function removes the white space in the left side of the word

*/
char *remove_left_space(char *word)
{
    if (word == NULL)
        return NULL;
	while (*word != '\0' && isspace(*word))
		word++;
		
	return word;	
}

bool ignored_line(char *line)
{
    line = remove_left_space(line);
    if (first_str_character(line, ';') || *line == '\0'
        || *line == '\n' || line == NULL)
        return true;    /** we ignoring this line */
    return false;    
}


/* This function copy the first word of source to destination */
void str_copy(char** destination, char* source)
{
  int size = 1, i=0;
  
  *destination = (char *) malloc(sizeof(char));
  check_if_memory_allocated(*destination)
  while(isspace(source[i])) {
    i++;
  }
  while (source[i] != '\0' && !isspace(source[i]))
  {
    (*destination)[size-1] = source[i];
    *destination = (char *) realloc(*destination, sizeof(char) * (++size));
    check_if_memory_allocated(*destination)
    i++;
    
  }
  (*destination)[size-1] = '\0';
  check_if_memory_allocated(*destination)
  /* adding '\0' to end of string. */
}
