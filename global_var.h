#ifndef GLOBAL_VAR
#define GLOBAL_VAR

#define _DATA 0
#define _STRING 1
#define _STRUCT 2
#define _ENTRY 3
#define _EXTERN 4


typedef enum cmd_operands {
    NO_OPERAND = 0,
    ONE_OPERAND,
    TWO_OPERANDS
} cmd_operands;


typedef enum cmd_syntx {
  ALL,
  NONE,
  NOT_CONSTANT,
  LABEL
} cmd_syntax;


typedef enum addressing_type {
	_immediate = 0,
	_direct = 1,
	_relative = 2,
	_reg = 3,
	none_adrress = -1
} addressing_type;


typedef enum reg_list {
	r0 = 0,
	r1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	none_reg = -1
}regs;	
	
/** command table of the assembly language */		
typedef struct command_table  {
  char *cmd;
  int op_code;
  cmd_syntax srcSyntx;
  cmd_syntax destSyntx;
} command_table ;


extern char *reg_name[8];
extern unsigned int line_cnt;	

extern char *two_operands_cmd[];
extern char *one_operands_cmd[];
extern char *zero_operands_cmd[];
extern char *regs_list[];
extern char *instruction_type[];
extern char *macroRelated[];

extern unsigned int DC;
extern unsigned int IC;

extern char* inst_types [5];
extern command_table  global_table[16];
extern const char delim [4];
extern const char delim_check [3];


#endif


