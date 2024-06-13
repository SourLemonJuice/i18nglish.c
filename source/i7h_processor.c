#include "i7h_processor.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* private functions prototype */
// get the length of a integer
int get_int_length(int src_int);

int i7h_processor(struct i7h_data_struct i7h_data[restrict], const char src_string[restrict])
{
    /* init */
    // free structure.buffer
    if(i7h_data->buffer != NULL)
        free(i7h_data->buffer);
    // get length
    int src_string_length = strlen(src_string);
    // get buffer size
    // +2 is first and end char
    // last +1 is \0
    i7h_data->buffer_size = get_int_length(src_string_length - 2) + 2 + 1;

    /* create buffer and processing */
    // if only have 2 chars, just return them
    if(src_string_length <= 2)
    {
        i7h_data->buffer = malloc(3);
        strcpy(i7h_data->buffer, src_string);
        return 0;
    }
    else // normal one
    {
        i7h_data->buffer = malloc(i7h_data->buffer_size);
        if(snprintf(i7h_data->buffer, i7h_data->buffer_size, "%c%d%c", src_string[0], src_string_length - 2, src_string[src_string_length - 1]) >= 0)
            return 0;
        else
            return 1;
    }
}

int i7h_reset_structure(struct i7h_data_struct i7h_data[restrict])
{
    if(i7h_data->buffer != NULL)
        free(i7h_data->buffer);
    i7h_data->buffer_size = 0;

    return 0; // TODO no error detection here
}

int get_int_length(int src_int)
{
    int length = 1;
    for(; src_int > 10; length++)
        src_int /= 10;
    return length;
}
