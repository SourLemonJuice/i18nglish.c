#ifndef I7H_PROCESSOR_H_
#define I7H_PROCESSOR_H_

#include <stddef.h>

/* structures */
struct i7h_data_struct
{
    char *buffer;
    size_t buffer_size;
};

/* functions */
// main i7h processor
int i7h_processor(struct i7h_data_struct i7h_data[restrict], const char src_string[]);
// free buffer(if have)
int i7h_reset_structure(struct i7h_data_struct i7h_data[restrict]);

#endif
