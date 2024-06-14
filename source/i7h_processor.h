#ifndef I7H_PROCESSOR_H_
#define I7H_PROCESSOR_H_

#include <stddef.h>

/* structures */
struct I7hDataStruct {
    char *buffer;
    size_t now_buffer_size;
    size_t real_buffer_size;
    int src_string_length;
};

/* enumerates */
enum I7hResultType {
    I7hOK = 0,
    I7hErrorAllocMemory = 1,
    I7hErrorFreeMemory,
};

/* functions */
// main i7h processor
int i7hProcessor(struct I7hDataStruct i7h_D[restrict], const char src_string[]);
// init structure
int i7hInitStructure(struct I7hDataStruct i7h_D[restrict]);
// free buffer(if have)
int i7hFreeStructure(struct I7hDataStruct i7h_D[restrict]);

#endif
