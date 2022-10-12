#include "translate.h"

/* prints out the command table and data table to the ob file */
void translate(word_list command_table, word_list data_table, char *fileName) 
{
    FILE *obFile;
    char *ICptr, *DCptr;
    
    ICptr = translateNumTo32(IC);
    DCptr = translateNumTo32(DC+1);
  
    obFile = openFile(fileName, "ob");
    fprintf(obFile, "%s %s\n", ICptr, DCptr);

	free(ICptr);
	free(DCptr);
	
    printTable(obFile, command_table);
    printTable(obFile, data_table);
}

/* prints a word list to obFile */
void printTable(FILE *obFile, word_list table) 
{
    word_node *ptr = table.head;
    char *word32;
    static int i = 100;	/* we need to check if IC and DC are correct */

    while (ptr) 
    {
        word32 = translateNumTo32(i);
        fprintf(obFile, "%s 	", word32);
		free(word32);
		
        word32 = translateTo32(ptr->word);
        fprintf(obFile, "%s\n", word32);
		free(word32);
        i++;
        ptr = ptr->next;
    }
}

/* translate a word to the special 32-base */
char * translateTo32(Word word) 
{
    unsigned int toTrans = 0;
    char *res = NULL;
    switch(word.type) 
    {
        case reg:
            toTrans += word.word.reg.ARE;
            toTrans += word.word.reg.destReg << 2;
            toTrans += word.word.reg.srcReg << 6;
            break;
        case adress_num:
            toTrans += word.word.adnum.ARE;
            toTrans += word.word.adnum.NUM << 2;
            break;
        case cmd:
            toTrans += word.word.cmd.ARE;
            toTrans += word.word.cmd.dest << 2;
            toTrans += word.word.cmd.src << 4;
            toTrans += word.word.cmd.op_code << 6;
            break;
        case data:
            toTrans += word.word.data.DATA;
            break;
        default:
            break;
    }
    res = translateNumTo32(toTrans);
    return res;
}


/* translate n to 32-base */
char *translateNumTo32(int n) 
{
    char *res = (char *)malloc(3 * sizeof(char));
    int firstHalf = n & (31);
    
    int secondHalf = (n & (31 << 5)) >> 5;
   
    res[0] = table32[secondHalf];
    res[1] = table32[firstHalf];
    res[2] = 0;
    
    return res;
}
