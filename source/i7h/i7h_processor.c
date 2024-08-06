#include "i7h_processor.h"

#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

/*
    get the length of a integer

    100 -> 3, 1000 -> 4
 */
static int getIntLength_(int src_int)
{
    int length = 1;
    for (; src_int > 10; length++)
        src_int /= 10;
    return length;
}

/*
    Resize the i7h buffer.

    Result:
        - true: ok
        - false: error
 */
static bool bufferRealloc_(struct I7hDataStruct data[restrict])
{
    data->real_buffer_size = data->need_buffer_size + 32; // for redundancy, realSize is (nowSize + 32)
    data->buffer = realloc(data->buffer, data->real_buffer_size);
    if (data->buffer == NULL)
        return false;

    return true;
}

int i7hInitStructure(struct I7hDataStruct i7h_D[restrict])
{
    i7h_D->need_buffer_size = 0;
    i7h_D->real_buffer_size = 3; // two char + one '\0', is default

    i7h_D->buffer = malloc(i7h_D->real_buffer_size); // default size is 3
    if (i7h_D->buffer == NULL)
        return kI7hErrorAllocMemory;

    return kI7hOK;
}

int i7hFreeStructure(struct I7hDataStruct i7h_D[restrict])
{
    if (i7h_D->buffer != NULL) {
        free(i7h_D->buffer);
    } else {
        return kI7hErrorFreeMemory;
    }

    return kI7hOK;
}

/*
    For single word parsing. Won't care punctuation.

    i7h_D means "i7h data structure"
 */
int i7hParserString(struct I7hDataStruct i7h_D[restrict], const char src_string[])
{
    /* get length */
    i7h_D->src_string_length = strlen(src_string);
    /* get buffer size */
    // +2 is first and end char, last +1 is \0
    i7h_D->need_buffer_size = getIntLength_(i7h_D->src_string_length - 2) + 2 + 1;

    /* update max usage memary size of buffer */
    if (i7h_D->need_buffer_size > i7h_D->real_buffer_size) {
        // and expand real buffer size
        if (bufferRealloc_(i7h_D) != true)
            return kI7hErrorAllocMemory;
    }

    // if only have 2 chars, just return them
    if (i7h_D->src_string_length <= 2) {
        strcpy(i7h_D->buffer, src_string);
        return kI7hOK;
    }

    // normal one
    if (snprintf(i7h_D->buffer, i7h_D->need_buffer_size, "%c%d%c", src_string[0], i7h_D->src_string_length - 2,
                 src_string[i7h_D->src_string_length - 1]) >= 0) {
        return kI7hOK;
    } else {
        return kI7hErrorStd;
    }
}

/*
    The stream version of i7h processor.
    Built-in perfect punctuation detection feature.

    WoW

    return non 0: error
 */
int i7hParserStream(FILE *stream, FILE *output)
{
    struct I7hDataStruct data;
    i7hInitStructure(&data);

    char ch;
    int word_pos = 0;

    while ((ch = getc(stream)) != EOF) {
        // if it's the end of a word
        if (ch == ' ' or ch == '\n' or ispunct(ch)) {
            // if buffer still blank
            if (word_pos == 0) {
                fputc(ch, output);
                continue;
            }

            // output the result string
            data.buffer[word_pos] = '\0'; // // now, the word_pos and strlen(buffer) are the same
            if (word_pos <= 2) {
                fputs(data.buffer, output);
            } else {
                fputc(data.buffer[0], output);
                fprintf(output, "%d", word_pos - 2);
                fputc(data.buffer[word_pos - 1], output);
            }
            fputc(ch, output); // don't forget the char in the current loop
            fflush(output); // finish

            // reset
            word_pos = 0;
            continue;
        }

        // if buffer size not enough, expand it
        if (word_pos >= data.real_buffer_size) {
            data.need_buffer_size += 1;
            if (bufferRealloc_(&data) != true)
                return kI7hErrorAllocMemory;
        }

        data.buffer[word_pos] = ch;
        word_pos++;
    }

    i7hFreeStructure(&data);
    return kI7hErrorStd;
}
