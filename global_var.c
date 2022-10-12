#include "global_var.h"

unsigned int DC = 0;
unsigned int IC = 0;

/** Global table - Contains all the commands in the languae */
command_table  global_table[] = {
    {"mov", 0, ALL, NOT_CONSTANT},
    {"cmp", 1, ALL, ALL},
    {"add", 2, ALL, NOT_CONSTANT},
    {"sub", 3, ALL, NOT_CONSTANT},
    {"not", 4, NONE, NOT_CONSTANT},
    {"clr", 5, NONE, NOT_CONSTANT},
    {"lea", 6, LABEL, NOT_CONSTANT},
    {"inc", 7, NONE, NOT_CONSTANT},
    {"dec", 8, NONE, NOT_CONSTANT},
    {"jmp", 9, NONE, NOT_CONSTANT},
    {"bne", 10, NONE, NOT_CONSTANT},
    {"get", 11, NONE, NOT_CONSTANT},
    {"prn", 12, NONE, ALL},
    {"jsr", 13, NONE, NOT_CONSTANT},
    {"rts", 14, NONE, NONE},
    {"hlt", 15, NONE, NONE}
  };

command_table  NULL_COMMAND = {"null", -1, NONE, NONE};

/** Guidence instruction type */
char *inst_types [] = {
	".data",
	".string",
	".struct",
	".entry",
	".extern"
};

  const char delim [4] ="\t, ";
  const char delim_check [3] ="\t ";

char *two_operands_cmd[] = {
                            "mov",
                            "cmp",
                            "add",
                            "sub",
                            "lea"
                          };


char *one_operands_cmd[] = {
                            "not",
                            "clr",
                            "inc",
                            "dec",
                            "jmp",
                            "bne",
                            "get",
                            "prn",
                            "jsr"
                          };



char *zero_operands_cmd[] = {
                            "rts",
                            "hlt"
                          };


char *regs_list[] = {
                     "r0",
                     "r1",
                     "r2",
                     "r3",
                     "r4",
                     "r5",
                     "r6",
                     "r7"
                    };

char *instruction_type[] = {
                            ".data",
                            ".string",
                            ".struct",
                            ".entry",
                            ".extern"
};      

char * macroRelated[] = {
                         "macro",
                         "endmacro"
};


