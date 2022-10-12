#include "symbol_table.h"
#include "funcs.h"
#include "extern_list.h"
#include "global_var.h"


/**
* The method acts as the first pass in the assembler actions, the function fills command table with commands and empty words to be
* filled by the second pass. it also fills data table, ext list and the label table.
* @param src the macro expanded source file (eg. {file name}.am).
* @param command_table an empty word list to be filled with commands.
* @param data_table an empty word list to be filled with data.
* @param head an empty word list to be filled with labels.
* @param extlst an empty extern list to be filled with the extern and entry labels.
* @return boolean of wether or not the first pass got an error
*/
bool first_pass(FILE *src, word_list *command_table, word_list *data_table, table_head *head, extern_list *extlst);


/**
* The method gets a line and analyze the data of the line
* @param line the line
* @param label_head Points to the head of the symbol table
* @param lineNum the line number in the source file
* @param command_table Points to the command table
* @param data_table Points to the data table
* @param extlst Points to the head of the extern table
*/
void process_line_f_pass(char *line, table_head *label_head, int lineNum,word_list *command_table, word_list *data_table, extern_list *extlst);


/**
* The method receives a line, a line number and a pointer to the word table
* and parses the command. 
* If the input is correct, the method will insert the input into the command table 
* @param line the line
* @param line_num the line number in the source file
* @param command_table Points to the command table
*/
void handle_command(char *line, int line_num, word_list *command_table);


/**
* The method receives a row and a row number and a pointer to the data table.
* The method analyzes the addressing type,depending on the addressing method, 
* inserts the values ​​into the data table
* @param line data type name
* @param data_type the method addressing type
* @param line_num the line number in the source file
* @param data_table Points to the data table
*/
void handle_data_str_struct(char *name, int data_type, int line_num, word_list *data_table);


/**
* The method receives a pointer to the head of the symbol table and after
* the first pass the method updates all the data nodes in the symbol table.
* @param _head Points to the head of the symbol table.
* @param IC the program instruction count
*/
void update_data_nodes(table_head *_head, unsigned int IC);


/**
* The method receives a pointer to the head of the data table and pointer that points to the data 
* that we want to insert to data table and the length of the data. and inserts the data 
* into the data table.
* @param data_table Pointer to data table.
* @param dataToInsert Pointer that points to the data 
* @param lenght The length of the data.
*/
void insertData(word_list *data_table, data_word **dataToInsert, int length);


/**
* The method receives a line and line number and the length of the struct to insert 
* and analyzes the struct. If successful, the method will insert the struct
* into the data table
* @param line The line from the source file
* @param lenght The length of the data.
* @param lineNum The line number in the source file
* @return Pointer that points to the data to insert.
*/
data_word ** analysStruct(char *line, int *length, int lineNum);


/**
* The method receives a line and line number and the length of the string to insert 
* and analyzes the string. If successful, the method will insert the string
* into the data table
* @param line The line from the source file
* @param lenght The length of the data.
* @param skip skip the line flag
* @param lineNum The line number in the source file
* @return Pointer that points to the string to insert.
*/
data_word ** analysString(char *line, int *length, bool skip, int lineNum);


/**
* The method receives a line and line number and the length of the data to insert 
* and analyzes the data. If successful, the method will insert the data
* into the data table
* @param line The line from the source file
* @param lenght The length of the data.
* @param lineNum The line number in the source file
* @return Pointer that points to the data to insert.
*/
data_word **analysData(char *line, int *length, int lineNum);
