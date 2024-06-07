#include <stdbool.h>
#include <stdint.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i7n_processor(char *buffer, size_t buffer_size, const char *src_string)
{
    // get length
    int src_string_length = strlen(src_string);

    // if only have 2 chars, just return them
    if(src_string_length <= 2)
    {
        strcpy(buffer, src_string);
        return 0;
    }

    if(snprintf(buffer, buffer_size, "%c%d%c", src_string[0], src_string_length - 2, src_string[src_string_length - 1]) >= 0)
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[])
{
    // handle CLI inputs
    if(argc < 2 or argc > 2)
    {
        puts("ERROR: Input Arguments Invalid");
        exit(1);
    }

    // create buffer
    const int buffer_size = 10;
    char buffer[buffer_size];
    // call the main function
    if(not i7n_processor(buffer, buffer_size, argv[1]))
        puts(buffer);
    else
    {
        puts("Error: Something Wrong While Processing");
        exit(1);
    }

    // exit
    exit(0);
    // default return
    return 0;
}
