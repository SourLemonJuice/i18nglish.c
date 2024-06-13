#include "i7h_processor.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* private functions prototype */
// get the length of a integer
int get_int_length(int src_int);

// i7h_D means "i7h data structure"
int i7h_processor(struct i7h_data_struct i7h_D[restrict], const char src_string[])
{
    /* get length */
    i7h_D->src_string_length = strlen(src_string);
    /* get buffer size */
    // +2 is first and end char, last +1 is \0
    i7h_D->nowBufferSize = get_int_length(i7h_D->src_string_length - 2) + 2 + 1;
    /* update max usage memary size of buffer */
    if (i7h_D->nowBufferSize > i7h_D->realBufferSize) {
        i7h_D->realBufferSize = i7h_D->nowBufferSize * 1.2; // for redundancy, realSize is (nowSize * 1.2)
        // and expand real buffer size
        i7h_D->buffer = realloc(i7h_D->buffer, i7h_D->realBufferSize); // TODO error detection of realloc
    }

    /* create buffer and processing */
    // if only have 2 chars, just return them
    if (i7h_D->src_string_length <= 2) {
        strcpy(i7h_D->buffer, src_string);
        return 0;
    } else {
        // normal one
        if(snprintf(i7h_D->buffer, i7h_D->nowBufferSize, "%c%d%c", src_string[0], i7h_D->src_string_length - 2, src_string[i7h_D->src_string_length - 1]) >= 0) {
            return 0;
        } else {
            return 1;
        }
    }
}

int i7h_init_structure(struct i7h_data_struct i7h_D[restrict])
{
    i7h_D->nowBufferSize = 0;
    i7h_D->realBufferSize = 3; // two char + one '\0', is default
    i7h_D->buffer = malloc(i7h_D->realBufferSize); // default size is 3

    return 0; // TODO error detection
}

int i7h_free_structure(struct i7h_data_struct i7h_D[restrict])
{
    if(i7h_D->buffer != NULL)
        free(i7h_D->buffer);

    return 0; // TODO no error detection here
}

int get_int_length(int src_int)
{
    int length = 1;
    for(; src_int > 10; length++)
        src_int /= 10;
    return length;
}
