#include "funcs.h"

/** This mehted inserts words into the word list */
void insert (word_list *word_list_table, Word word) 
{
    word_node *curr_word_node = malloc(sizeof(word_node));
    check_if_memory_allocated(curr_word_node)
    curr_word_node->word = word;
    curr_word_node->next = NULL;
    curr_word_node->prev = word_list_table->tail;
    
    if (!word_list_table->head) 
    {
        word_list_table->head = curr_word_node;
    }

    if (word_list_table->tail) 
    {
        word_list_table->tail->next = curr_word_node;
    }
    word_list_table->tail = curr_word_node;
}


/** create an empty word in word list.
 * in second pass filling those empty lines
 */
void insert_empty_line(word_list *lst, int n) 
{
    int i;
    immediate_opcode EmptyWord = {0,0};
    union generate_command_opcode tempUnion;
    Word tempWord;

    tempUnion.adnum = EmptyWord;
    tempWord.word = tempUnion;
    tempWord.type = empty;

    for (i=0; i<n; i++) 
    {
        insert(lst, tempWord);
    }
}


/** free the allocated memory for word list */
void freeList(word_list lst) 
{
    word_node *word, *tmp;
    word = lst.head;
    while(word) 
    {
        tmp = word->next;
        free(word);
        word = tmp;
    }
}


void printList(word_list lst) 
{
    word_node *word = lst.head;
    
    while(word) 
    {
        switch(word->word.type) 
        {
            case reg:
                printf("%d %d %d\n", word->word.word.reg.srcReg, word->word.word.reg.destReg, word->word.word.reg.ARE);
                break;
            case adress_num:
                printf("%d %d\n",  word->word.word.adnum.NUM, word->word.word.adnum.ARE);
                break;
            case cmd:
                printf("%d %d %d %d\n", word->word.word.cmd.op_code, word->word.word.cmd.src, word->word.word.cmd.dest, word->word.word.cmd.ARE);
                break;
            case data:
                printf("%d\n", word->word.word.data.DATA);
                break;
            case empty:
                printf("empty\n");
                break;
            default:
                printf("def\n");
                break;
        }
        word = word->next;
    }
    
}
