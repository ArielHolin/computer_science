/*******************************************************************************
*  ws5_ex2.c
*  Author: Ariel
*  Reviewer: Doron
*******************************************************************************/
#include <stdio.h>  /* printf, fopen, fgets, fputs, fclose , getc  */
#include <stddef.h> /* size_t                                      */
#include <string.h> /* strlen, strcmp, strncmp                     */

#define MAX_SIZE          50
#define SPECIAL_INPUT_LEN 5

const char *BUFFER_FILE_NAME = "buffer.txt";

typedef int (*cmpfunc_ptr_ty)(const char *,const char *);
typedef int (*action_ptr_ty)(const char *,const char *);

typedef struct Logger
{
	char *command;
	cmpfunc_ptr_ty compare;
	action_ptr_ty action;
} logger_ty;

/************************* Phase 1 Declarations *******************************/

int AddToEOF(char *file_name);

/************************* Phase 2 Declarations *******************************/

static void InitFunc(logger_ty array[]);

static int RemoveFile(const char *file_name, const char *buffer);
static int CountLines(const char *file_name, const char *buffer);
static int ExitFile(const char *file_name, const char *buffer);
static int CmpCharAtStart(const char *chr1, const char *chr2);
static int CopyFileContent(const char *file_name1, const char *file_name2);
static int AppendToFileStart(const char *file_name, const char *string);
static int CmpTrueFun(const char *user_input, const char *command);
static int AppendToEof(const char *file_name, const char *string);

/************************ Phase 3 Declarations ********************************/

enum status {Success, Open_File_Fail};
enum inputs {Remove, Count, Exit, Append_Start};
static int ValidateInput(const char *str, logger_ty array[]);
int Logger(char *file_name);

/************************* main ***********************************************/

int main(int argc, char **argv)
{	
	if ( 3 != argc )
	{
		printf("Usage: ./ws5 Phase1/2 {file_name}\n");
		return 1;
	}
	
	if ( 0 == strcmp(argv[1], "Phase1") )
	{
		AddToEOF(argv[2]);
		return 0;
	}
	
	if ( 0 == strcmp(argv[1], "Phase2") )
	{
		Logger(argv[2]);
		return 0;
	}
	
	printf("Usage: ./ws5 Phase1/2 {file_name}\n");
	return 1;	
}

/********************** Phase 1 Implemantation ********************************/

int AddToEOF(char *file_name)
{
	FILE *fp;
	char str[MAX_SIZE];
	
	fp = fopen(file_name, "a+");
	
	if ( fp == NULL )
	{
		printf("Error: Unable to open file\n");
		return 1;	
	}
	
	do
	{
		printf("Insert input: ");
		
		fgets(str, MAX_SIZE, stdin);
		
		if ( 0 == strcmp(str, "Exit\n"))
		{
			continue;
		}
		
		fputs(str, fp);
	}
	while (0 != strcmp(str, "Exit\n"));
	
	fclose(fp);
	
	return 0;
}

/********************** Phase 2 Implemantation ********************************/

int Logger(char *file_name)
{
	char str[MAX_SIZE];
	logger_ty structs[SPECIAL_INPUT_LEN];
	int special_input;
	
	InitFunc(structs);
	
	do
	{
		printf("Insert input: ");
		
		fgets(str, MAX_SIZE, stdin);
		
		special_input = ValidateInput(str, structs);
		
		switch (special_input)
		{
			case (Remove):
				structs[Remove].action(file_name, BUFFER_FILE_NAME);
				break;
			case (Count):
				structs[Count].action(file_name, BUFFER_FILE_NAME);
				break;
			case (Exit):
				structs[Exit].action(file_name, BUFFER_FILE_NAME);
				break;
			case (Append_Start):
				structs[Append_Start].action(file_name, str);
				break;
			default:
			structs[SPECIAL_INPUT_LEN - 1].action(file_name, str);
			break;
		}
	}
	while (Exit != special_input);
	
	return Success;
}

static int ValidateInput(const char *str, logger_ty array[])
{
	if (0 == array[Remove].compare(array[Remove].command, str)) return Remove;
	if (0 == array[Count].compare(array[Count].command, str)) return Count;
	if (0 == array[Exit].compare(array[Exit].command, str)) return Exit;
	if (0 == array[Append_Start].compare(array[Append_Start].command, str)) 
		return Append_Start;
	return SPECIAL_INPUT_LEN - 1;
}


/* Initializing array of structs */
static void InitFunc(logger_ty array[])
{
	array[Remove].command = "-remove\n";
	array[Remove].compare = strcmp;
	array[Remove].action = RemoveFile;

	array[Count].command = "-count\n";
	array[Count].compare = strcmp;
	array[Count].action = CountLines;
	
	array[Exit].command = "-exit\n";
	array[Exit].compare = strcmp;
	array[Exit].action = ExitFile;
	
	array[Append_Start].command = "<";
	array[Append_Start].compare = CmpCharAtStart;
	array[Append_Start].action = AppendToFileStart;
	
	array[SPECIAL_INPUT_LEN - 1].command = " ";
	array[SPECIAL_INPUT_LEN - 1].compare = CmpTrueFun;
	array[SPECIAL_INPUT_LEN - 1].action = AppendToEof;
}

/* Deleting file_name.  buffer is given to be consistent with declaration. */
static int RemoveFile(const char *file_name, const char *buffer)
{
	int res;
	
	res = remove(file_name);
	
	if ( 0 == res )
	{
		printf("File deleted successfully\n");
		return Success;
	}
	
	printf("Error: unable to remove file\n");
	return Open_File_Fail;
}

/* Counts lines in file. */
static int CountLines(const char *file_name,const char *buffer)
{
	FILE *fp;
	int counter = 0;
	char c;
	
	fp = fopen(file_name, "r+");
	
	if ( fp == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;	
	}
	
	while ( c != EOF )
	{
		c = getc(fp);
		
		if ( c == '\n')
		{
			++counter;
		}
	}
	
	fclose(fp);
	
	printf("Number of Lines in file: %d.\n", counter);
	return Success;
}

static int ExitFile(const char *file_name,const char *buffer)
{
	FILE *fp;
	
	fp  = fopen(file_name, "r+");
	
	if ( fp == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;
	}
	
	fclose(fp);
	return Success;
}

/* Comparing two chars. Used to compare chars at beginning of strings. */
static int CmpCharAtStart(const char *user_input,const char *command)
{
	return strncmp(user_input, command, 1);
}

/* Appending string to first line of file_name */
static int AppendToFileStart(const char *file_name,const char *string)
{
	FILE *fp1;
	FILE *fp2;
	char chr;
	int str_len = strlen(string) - 1;
	int i = 0;
	
	CopyFileContent(file_name, BUFFER_FILE_NAME);
	
	fp1 = fopen(file_name, "w+");
	
	if ( fp1 == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;	
	}
	
	fp2 = fopen("buffer.txt", "r+");
	
	if ( fp2 == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;	
	}
	
	while (i < str_len)
	{
		fputc(*(string + 1), fp1);
		++string;
		++i;
	}
	
	chr = fgetc(fp2);
	
	while ( chr != EOF )
	{
		fputc(chr, fp1);
		chr = fgetc(fp2);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	remove(BUFFER_FILE_NAME);
	
	return Success;
}

/* Copying file_name1 content to file_name2 */
static int CopyFileContent(const char *file_name1,const char *file_name2)
{
	FILE *fp1;
	FILE *fp2;
	char chr;
	
	fp1 = fopen(file_name1, "r+");
	
	if ( fp1 == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;	
	}
	
	fp2 = fopen(file_name2, "w+");
	
	if ( fp2 == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;
	}
	
	chr = fgetc(fp1);
	
	while ( chr != EOF )
	{
		fputc(chr, fp2);
		chr = fgetc(fp1);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	return Success;
}


static int CmpTrueFun(const char *chr1,const char *chr2)
{
	return 1;
}

/* Appending a string to last line of file_name */
static int AppendToEof(const char *file_name,const char *string)
{
	FILE *fp;
	int str_len = strlen(string);
	int i = 0;
	
	fp = fopen(file_name, "a+");
	
	if ( fp == NULL )
	{
		printf("Error: Unable to open file\n");
		return Open_File_Fail;	
	}
	
	while (i < str_len)
	{
		fputc(*string, fp);
		++string;
		++i;
	}
	
	fclose(fp);
	
	return Success;	
}








