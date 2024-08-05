#ifndef I7H_PROCESSOR_H_
#define I7H_PROCESSOR_H_

#include <stddef.h>
#include <stdio.h>

/* structures */
struct I7hDataStruct {
    char *buffer;
    size_t need_buffer_size;
    size_t real_buffer_size;
    int src_string_length; // I want more speed...
};

/* enumerates */
enum I7hResultType {
    kI7hOK = 0,
    kI7hErrorAllocMemory = 1,
    kI7hErrorFreeMemory,
};

/* functions */
// init structure
int i7hInitStructure(struct I7hDataStruct i7h_D[restrict]);
// free buffer(if have)
int i7hFreeStructure(struct I7hDataStruct i7h_D[restrict]);
// main i7h processor
int i7hProcessor(struct I7hDataStruct i7h_D[restrict], const char src_string[]);
// stream version processor
int i7hParserStream(FILE *stream, FILE *output);

#endif
