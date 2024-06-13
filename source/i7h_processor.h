#ifndef I7H_PROCESSOR_H_
#define I7H_PROCESSOR_H_

#include <stddef.h>

/* structures */
struct i7h_data_struct {
    char *buffer;
    size_t nowBufferSize;
    size_t realBufferSize;
    int src_string_length;
};

/* functions */
// main i7h processor
int i7h_processor(struct i7h_data_struct i7h_data[restrict], const char src_string[]);
// init structure
int i7h_init_structure(struct i7h_data_struct i7h_D[restrict]);
// free buffer(if have)
int i7h_free_structure(struct i7h_data_struct i7h_D[restrict]);

#endif
