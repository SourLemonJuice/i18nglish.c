#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

#include "i7h_processor.h"

int main(int argc, char *argv[])
{
    // handle CLI inputs
    if(argc < 2)
    {
        puts("ERROR: Input Arguments Invalid");
        exit(EXIT_FAILURE);
    }

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

    // exit
    exit(EXIT_SUCCESS);
}
