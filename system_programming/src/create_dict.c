#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>

#define MAX_WORD 50
int main(void)
{
    FILE *new_dict = NULL;
    FILE *dict_f = NULL;
    int errnum = 0;
    const char *header_g_ifnd = "#ifndef __DICTIONARY_H__";
    const char *header_g_def = "#define __DICTIONARY_H__";
    const char *header_g_end_def = "#endif /* __DICTIONARY_H__*/";

    const char *dict_arr = "char *dict_arr[] = {";
   
    char word_read[MAX_WORD];

    new_dict = fopen("../include/dictionary.h", "w");
  
    if(NULL==new_dict)
	{
	    errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
		return 0;
	}

    dict_f = fopen("/usr/share/dict/words", "r");

    if(NULL==dict_f)
	{
        fclose(new_dict);
		errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
		return 0;
	}

    fputs(header_g_ifnd, new_dict);
    fputs("\n", new_dict);
    fputs(header_g_def, new_dict);
    fputs("\n", new_dict);
    fputs(dict_arr, new_dict);
    fputs("\n", new_dict);
   
    while(EOF!=fscanf(dict_f, "%s", word_read))
    {
        fprintf(new_dict, "\"");
        fprintf(new_dict, word_read);
        fprintf(new_dict, "\",\n");
    }
    fseek(new_dict, -2, SEEK_CUR);
    fprintf(new_dict, "};\n");

    fprintf(new_dict, header_g_end_def);

    fclose(new_dict);
    fclose(dict_f);

    return 0;
}