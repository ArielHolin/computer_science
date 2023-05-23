/*******************************************************************************
*  calculator.c                                                                *
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
/******************************************************************************/
#include <stdio.h>  /*printf    */
#include <stdlib.h> /*strtod    */
#include <string.h> /*strlen    */
#include <assert.h> /*assert    */
#include <ctype.h>  /*isdigit() */

#include "stack.h"

#define ASCII_SIZE 				256
#define NUM_OF_OPERATORS 		4
#define STACK_SIZE 				ASCII_SIZE*sizeof(double)
#define STACK_CAPACITY 			STACK_SIZE

/*******************************************************************************/

enum first_op
{
	YES = 0,
	NO
};

enum calc_stacks
{
	OPERANDS = 0, 
	OPERATORS = 1, 
	NUM_OF_STACKS
};

typedef enum return_val
{
	SUCCESS = 0,
	SYNTAX_ERROR,
	MATH_ERROR,
	SYS_ERROR
}return_val_ty;
	
typedef enum states
{
	WAIT_1ST_NUM = 0,
	AFTER_1ST_UNARY,
	WAIT_NUM,
	WAIT_OP,
	ERROR, 
	STATES_NUM
}state_ty;

typedef enum precedence
{
	ADD= 0,
	SUBTRACT= 1, 
	MULTI = 2, 
	DIVISION = 3, 
	BRACKET = 4,
	TOTAL_OPS
}operation_num_ty;

enum associativity 
{
	LR = 0, 
	RL = 1
};

/*******************************************************************************/
typedef double (*calculation_func_ty)(double num1, double num2);

typedef struct operator
{
	int priority;
	int associativity;
	calculation_func_ty operation;
}operation_ty;

typedef struct calculator calculator_ty;

typedef int (*handler_func_ty)(void **data, calculator_ty *new_calculator,
													       state_ty next_state);

typedef struct state_handler
{
	state_ty current_state;
	state_ty next_state;
	handler_func_ty handler;
}handler_ty;

struct calculator
{
	handler_ty LUT_handlers[ASCII_SIZE][STATES_NUM];
	operation_ty LUT_operators[TOTAL_OPS];
	size_t LUT_to_operations[ASCII_SIZE];
	
	stack_ty *operator_stack;
	stack_ty *operand_stack;
	
	char operator_arr[ASCII_SIZE];
	double operand_arr[ASCII_SIZE];
	
};

static calculator_ty *CreateCalculator(void);
/*****************************************************************************/
static void DestroyCalculator(calculator_ty *calculator);

/****************************Initialization functions**************************/
static void InitLuts(calculator_ty *calculator);
/*****************************************************************************/
static void InitOperatorLut(calculator_ty *new_calculator);
/*****************************************************************************/
static void InitLutToOperations(calculator_ty *new_calculator);
/*****************************************************************************/
static void InitStateLutFunc(calculator_ty *new_calculator);
/*****************************************************************************/

/**********************************Handlers***********************************/

static int ClosedParenHandler(void **str, calculator_ty *new_calculator, 
															state_ty next_state);
/*****************************************************************************/
static int ErrorHandler(void **str, calculator_ty *new_calculator, state_ty next_state);
/*****************************************************************************/
static int NumberHandler(void **str, calculator_ty *new_calculator, state_ty next_state);
/*****************************************************************************/
static int UnaryOperatorHandler(void **str, calculator_ty *new_calculator, 
state_ty next_state);
/*****************************************************************************/
static int OperatorHandler(void **str, calculator_ty *new_calculator, 
															state_ty next_state);
/*****************************************************************************/
static int AdvanceHandler(void **str, calculator_ty *new_calculator, 
														   state_ty next_state);
/*****************************************************************************/
static int OpenParenHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_state);
/*****************************calculation functions****************************/
static double AdditionFunc(double data1, double data2);
/*****************************************************************************/
static double SubtructFunc(double data1, double data2);
/*****************************************************************************/
static double MultiFunc(double data1, double data2);
/*****************************************************************************/
static double DivFunc(double data1, double data2);
/*****************************************************************************/
static double PopAndCalc(calculator_ty *calculator);
/******************************************************************************/
static void Pops(calculator_ty *calculator);
/******************************************************************************/
/******************************************************************************/
static calculator_ty *CreateCalculator(void)
{
	calculator_ty *calculator = (calculator_ty *)malloc(sizeof(calculator_ty));
	
	if (NULL == calculator)
	{
		return NULL;
	}
	
	/* allocate operator and operand stacks */	
	calculator->operator_stack = StackCreate(STACK_CAPACITY);
	calculator->operand_stack = StackCreate(STACK_CAPACITY);
	
	return calculator;
}

int Calculate(const char *str_const, double *result)
{
	char *str = (char *)str_const;
	state_ty current_state = 0;
	state_ty next_state = 0;
	
	calculator_ty *calculator = CreateCalculator();
	InitLuts(calculator);
	current_state = WAIT_1ST_NUM;
	next_state = calculator->LUT_handlers[*str][WAIT_1ST_NUM].next_state;
	
	while (*str != '\0' && current_state != ERROR)
	{	
		/*calling the LUT for the handler*/
		current_state = calculator->LUT_handlers[*str][current_state].handler
												((&str), calculator, next_state);
		next_state = calculator->LUT_handlers[*str][current_state].next_state;
	}

	*result = PopAndCalc(calculator);
	DestroyCalculator(calculator);
	
	return(SUCCESS);
}

/******************************************************************************/
static void DestroyCalculator(calculator_ty *calculator)
{
	assert (NULL != calculator);
	StackDestroy(calculator->operator_stack);
	StackDestroy(calculator->operand_stack);
	free(calculator);	
}

/********************************Helper Functions******************************/
/******************************************************************************/
static double PopAndCalc(calculator_ty *calculator)
{
	double *num_arr = calculator->operand_arr;
	double var1 = 0;
	double var2 = 0;
	char sym = 0;
	double sum_res = 0;

	while (!StackIsEmpty(calculator->operator_stack))
	{
		Pops(calculator);
	}	
		
	if (!StackIsEmpty(calculator->operand_stack))
	{
		sum_res= *(double*)StackPeek(calculator->operand_stack);
		StackPop(calculator->operand_stack);
	}
	
	return (sum_res);
}

/******************************************************************************/
static int NumberHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_st)
{
	char **str = (char**)str_const;
	stack_ty *num_stack = calculator->operand_stack;
	double *num_arr = calculator->operand_arr;
	
	/*num_arr[] - array of double nums to push on to the stack*/
	num_arr[StackSize(num_stack)] = strtod(*str, str);
	StackPush(num_stack, &num_arr[StackSize(num_stack)]);

	return(next_st);
}

/******************************************************************************/
static int OperatorHandler(void **str_const, calculator_ty *calculator, 
															  state_ty next_st)
{
	char **str = (char**)str_const;
	char *op_arr = calculator->operator_arr; 
	stack_ty *op_stack = calculator->operator_stack;
	size_t  *LUT_to_operations = calculator->LUT_to_operations;
	operation_ty *LUT_operators = calculator->LUT_operators;

/*check if recieved operator < previous operator.if yes, calculate last exp*/
	while(!StackIsEmpty(op_stack) && 
		LUT_operators[LUT_to_operations[**(char**)str]].priority <= 
	LUT_operators[LUT_to_operations[*(char*)StackPeek(op_stack)]].priority 
									&& *(char*)StackPeek(op_stack) != '(')
	{
		Pops(calculator);
	}
	
	op_arr[StackSize(op_stack)] = **(char**)str;
	StackPush(op_stack, &op_arr[StackSize(op_stack)]);
	(*str)++;

	return(next_st);
}

/******************************************************************************/
static int ClosedParenHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_st)
{
	char **str = (char**)str_const;
	stack_ty *op_stack = calculator->operator_stack;
	size_t  *LUT_to_operations = calculator->LUT_to_operations;
	operation_ty *LUT_operators = calculator->LUT_operators;
	
	while (*(char*)StackPeek(calculator->operator_stack) != '(' && !StackIsEmpty(op_stack) && 
	LUT_operators[LUT_to_operations[**(char**)str_const]].priority <= 
		LUT_operators[LUT_to_operations[*(char*)StackPeek(op_stack)]].priority)
	{
		Pops(calculator);
	}
	
	StackPop(op_stack);
	
	(*str)++;
	
	return(next_st);
}

/******************************************************************************/
static void Pops(calculator_ty *calculator)
{
	double *num_arr = calculator->operand_arr;
	double var1 = 0;
	double var2 = 0;
	char sym = 0;
	
	var1= *(double *)StackPeek(calculator->operand_stack);
	StackPop(calculator->operand_stack);

	sym = *(char *)StackPeek(calculator->operator_stack);
	StackPop(calculator->operator_stack);

	var2= *(double *)StackPeek(calculator->operand_stack);
	StackPop(calculator->operand_stack);

/*	call callculation func*/
	num_arr[StackSize(calculator->operand_stack)] = 
	calculator->LUT_operators[calculator->LUT_to_operations[sym]].operation
																(var1,var2);
/*	push res to stack*/
	StackPush(calculator->operand_stack, 
							&num_arr[StackSize(calculator->operand_stack)]);
}

/******************************************************************************/
static int UnaryOperatorHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_state)
{
	char **str = (char**)str_const;
	stack_ty *operand_stack = calculator->operand_stack;
	double *num_arr = calculator->operand_arr;

	if(*(*str+1) == '(')
	{
		(*str)++;
		
		return(WAIT_1ST_NUM);
	}
	
	if(!(isdigit(*(*str+1))))
	{
		return(ERROR);
	}
	
	(*str)--;
	
	calculator->operand_arr[StackSize(calculator->operand_stack)] = 
															strtod(*str, str);
	StackPush(calculator->operand_stack, &num_arr[StackSize(operand_stack)]);

	return(WAIT_OP);
}
/******************************************************************************/
static int AdvanceHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_state)
{
	char **str = (char**)str_const;
	(*str)++;

	return(next_state);
}

/******************************************************************************/
static int OpenParenHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_state)
{
	char **str = (char**)str_const;
	char *op_arr = calculator->operator_arr; 
	stack_ty *op_stack = calculator->operator_stack;
	
	op_arr[StackSize(op_stack)] = **(char**)str_const;
	StackPush(op_stack, &op_arr[StackSize(op_stack)]);
	
	(*str)++;

	return(next_state);
}

/******************************************************************************/
static int ErrorHandler(void **str_const, calculator_ty *calculator, 
															state_ty next_st)
{
	return(SYNTAX_ERROR);
}
/******************************************************************************/
static double AdditionFunc(double data1, double data2)
{
	return(data1+data2);
}
/******************************************************************************/
static double SubtructFunc(double data1, double data2)
{
	return(data2-data1);
}
/******************************************************************************/
static double MultiFunc(double data1, double data2)
{
	return(data2*data1);
}
/******************************************************************************/
static double DivFunc(double data1, double data2)
{
	return(data2/data1);
}
/******************************************************************************/
/***********************Initialization functions*******************************/
static void InitLuts(calculator_ty * calculator)
{
	InitStateLutFunc(calculator);
	InitOperatorLut(calculator);
	InitLutToOperations(calculator);
}

static void InitStateLutFunc(calculator_ty *calculator)
{
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_handlers[i][ERROR].handler = ErrorHandler;
		calculator->LUT_handlers[i][ERROR].current_state = ERROR;
		calculator->LUT_handlers[i][ERROR].next_state = ERROR;
	}
	
	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_handlers[i][WAIT_1ST_NUM].handler = ErrorHandler;
		calculator->LUT_handlers[i][WAIT_1ST_NUM].current_state = WAIT_1ST_NUM;
		calculator->LUT_handlers[i][WAIT_1ST_NUM].next_state = ERROR;
	}
	
	for (i = '0'; i <= '9'; i++)
	{
		calculator->LUT_handlers[i][WAIT_1ST_NUM].handler = NumberHandler;
		calculator->LUT_handlers[i][WAIT_1ST_NUM].current_state = WAIT_1ST_NUM;
		calculator->LUT_handlers[i][WAIT_1ST_NUM].next_state = WAIT_OP;
	}
	
	i = '+';
	
	calculator->LUT_handlers[i][WAIT_1ST_NUM].handler = UnaryOperatorHandler;
	calculator->LUT_handlers[i][WAIT_1ST_NUM].current_state = WAIT_1ST_NUM;
	calculator->LUT_handlers[i][WAIT_1ST_NUM].next_state = AFTER_1ST_UNARY;
	
	i = '-';
	
	calculator->LUT_handlers[i][WAIT_1ST_NUM].handler = UnaryOperatorHandler;
	calculator->LUT_handlers[i][WAIT_1ST_NUM].current_state = WAIT_1ST_NUM;
	calculator->LUT_handlers[i][WAIT_1ST_NUM].next_state = AFTER_1ST_UNARY;

	calculator->LUT_handlers['('][WAIT_1ST_NUM].handler = OpenParenHandler;
	calculator->LUT_handlers['('][WAIT_1ST_NUM].current_state = WAIT_1ST_NUM;
	calculator->LUT_handlers['('][WAIT_1ST_NUM].next_state = WAIT_1ST_NUM;

	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].handler = ErrorHandler;
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].current_state = 
																AFTER_1ST_UNARY;
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].next_state = ERROR;
	}
	
	for (i = '0'; i <= '9'; i++)
	{
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].handler = 
														UnaryOperatorHandler;
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].current_state = 
																AFTER_1ST_UNARY;
		calculator->LUT_handlers[i][AFTER_1ST_UNARY].next_state = WAIT_OP;
	}
	
	calculator->LUT_handlers['('][AFTER_1ST_UNARY].handler = OpenParenHandler;
	calculator->LUT_handlers['('][AFTER_1ST_UNARY].current_state = 
																AFTER_1ST_UNARY;
	calculator->LUT_handlers['('][AFTER_1ST_UNARY].next_state = WAIT_1ST_NUM;

	j = WAIT_NUM;
	
	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_handlers[i][j].handler = ErrorHandler;
		calculator->LUT_handlers[i][j].current_state = WAIT_NUM;
		calculator->LUT_handlers[i][j].next_state = ERROR;
	}
	
	for (i = '0'; i <= '9'; i++)
	{
		calculator->LUT_handlers[i][j].handler = NumberHandler;
		calculator->LUT_handlers[i][j].current_state = WAIT_NUM;
		calculator->LUT_handlers[i][j].next_state = WAIT_OP;
	}
	
	calculator->LUT_handlers['('][j].handler = OpenParenHandler;
	calculator->LUT_handlers['('][j].current_state = WAIT_NUM;
	calculator->LUT_handlers['('][j].next_state = WAIT_NUM;
	
	i = '+';
	
	calculator->LUT_handlers[i][j].handler = NumberHandler;
	calculator->LUT_handlers[i][j].current_state = WAIT_NUM;
	calculator->LUT_handlers[i][j].next_state = WAIT_OP;
	
	i = '-';
	
	calculator->LUT_handlers[i][j].handler = NumberHandler;
	calculator->LUT_handlers[i][j].current_state = WAIT_NUM;
	calculator->LUT_handlers[i][j].next_state = WAIT_OP;
	
	j = WAIT_OP;
	
	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_handlers[i][j].handler = ErrorHandler;
		calculator->LUT_handlers[i][j].current_state = WAIT_OP;
		calculator->LUT_handlers[i][j].next_state = ERROR;
	}
	
	calculator->LUT_handlers['+'][j].handler = OperatorHandler;
	calculator->LUT_handlers['+'][j].current_state = WAIT_OP;
	calculator->LUT_handlers['+'][j].next_state = WAIT_NUM ;
	
	calculator->LUT_handlers['-'][j].handler = OperatorHandler;
	calculator->LUT_handlers['-'][j].current_state = WAIT_OP;
	calculator->LUT_handlers['-'][j].next_state = WAIT_NUM;
	
	calculator->LUT_handlers['*'][j].handler = OperatorHandler;
	calculator->LUT_handlers['*'][j].current_state = WAIT_OP;
	calculator->LUT_handlers['*'][j].next_state = WAIT_NUM;
	
	calculator->LUT_handlers['/'][j].handler = OperatorHandler;
	calculator->LUT_handlers['/'][j].current_state = WAIT_OP;
	calculator->LUT_handlers['/'][j].next_state = WAIT_NUM;

	calculator->LUT_handlers[')'][j].handler = ClosedParenHandler;
	calculator->LUT_handlers[')'][j].current_state = WAIT_OP;
	calculator->LUT_handlers[')'][j].next_state = WAIT_OP;
	
	for (j = 0 ; j < STATES_NUM; j++)
	{
		calculator->LUT_handlers[' '][j].handler = AdvanceHandler;
		calculator->LUT_handlers[' '][j].next_state = j;
		calculator->LUT_handlers[' '][j].current_state = j;
	}
}

/*****************************************************************************/
static void InitOperatorLut(calculator_ty *calculator)
{
	size_t i = 0;
	size_t j = 0;

	calculator->LUT_operators[0].priority = ADD;
	calculator->LUT_operators[0].associativity = LR;
	calculator->LUT_operators[0].operation = AdditionFunc;
	
	calculator->LUT_operators[1].priority = SUBTRACT;
	calculator->LUT_operators[1].associativity = LR;
	calculator->LUT_operators[1].operation = SubtructFunc;
	
	calculator->LUT_operators[2].priority = MULTI;
	calculator->LUT_operators[2].associativity = LR;
	calculator->LUT_operators[2].operation = MultiFunc;
	
	calculator->LUT_operators[3].priority = DIVISION;
	calculator->LUT_operators[3].associativity = LR;
	calculator->LUT_operators[3].operation = DivFunc;
	
	/* allocate operator and operand stacks */	
	calculator-> operator_stack = StackCreate(STACK_CAPACITY);
	calculator->operand_stack = StackCreate(STACK_CAPACITY);
}
/******************************************************************************/
static void InitLutToOperations(calculator_ty *calculator)
{
	size_t i = 0;
	
	for (i = 0 ; i < ASCII_SIZE; i++)
	{		
		calculator->LUT_to_operations[i] = 0;
	}
		
	calculator->LUT_to_operations['+'] = 0;
	calculator->LUT_to_operations['-'] = 1;
	calculator->LUT_to_operations['*'] = 2;
	calculator->LUT_to_operations['/'] = 3;
}


