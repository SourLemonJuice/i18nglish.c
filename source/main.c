#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i7h_processor.h"

int i7h_processor_argv(int argc, char *argv[], int argc_begin)
{
    // create i7h data
    struct i7h_data_struct i7h_data;
    // process all arguments
    for(int i = 1; i < argc; i++)
    {
        // call the main function
        if(i7h_processor(&i7h_data, argv[i]) == 0)
            printf("%s ", i7h_data.buffer);
        else
        {
            printf("Error: Something wrong while processing.\nLoop cycles is %d, string: %s\n", i, argv[i]);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");
    // free the buffer
    i7h_reset_structure(&i7h_data);

    return 0;
}

int i7h_processor_file(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen("a.temp", "r");
    char temp_string[128];

    // create i7h data
    struct i7h_data_struct i7h_data;

    while(not feof(file_handle) or ferror(file_handle))
    {
        fscanf(file_handle, "%s", temp_string);
        // call the main function
        if(i7h_processor(&i7h_data, temp_string) == 0)
            printf("%s ", i7h_data.buffer);
        else
        {
            printf("Error: Something wrong while processing.\nString: %s\n", temp_string);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");

    // free something
    i7h_reset_structure(&i7h_data);
    fclose(file_handle);

    return 0;
}

int main(int argc, char *argv[])
{
    // handle CLI inputs
    if(argc < 2)
    {
        puts("ERROR: Input Arguments Invalid");
        exit(EXIT_FAILURE);
    }
    // flags
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--help") == 0)
        {
            puts("echo --help ...");
            exit(1);
        }
        // --source_file
        if(strcmp(argv[i], "--source_file") == 0)
        {
            i++;
            if(i + 1 <= argc)
            {
                i7h_processor_file(argv[i]);
            }
            else
            {
                puts("Flag value ERROR");
                exit(1);
            }
            continue;
        }
    }

    // exit
    exit(EXIT_SUCCESS);
}
